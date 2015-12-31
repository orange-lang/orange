/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdexcept>

#include <grove/Module.h>
#include <grove/Namespace.h>
#include <grove/Builder.h>
#include <grove/MainFunction.h>
#include <grove/TypeProvider.h>

#include <grove/types/FunctionType.h>
#include <grove/types/IntType.h>

#include <grove/exceptions/file_error.h>
#include <grove/exceptions/fatal_error.h>

#include <util/file.h>
#include <util/assertions.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetSubtargetInfo.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/Scalar.h>

bool Module::BlockIterator::useContextStack() const
{
	// We want to use the context stack if and only if
	// the module is parsing and (the m_ptr is not
	// the top block or m_ptr it's a block in general).
	return m_module->getParsing() &&
		(m_ptr != m_module->getBlock() ||
		 dynamic_cast<Block *>((ASTNode *)m_ptr) != nullptr);
}

bool Module::BlockIterator::hasNext() const
{
	if (useContextStack())
	{
		return m_ctx_stack.size() > 0;
	}
	else
	{
#ifdef DEBUG_BUILD
		// If we fell back here but there's no next,
		// there's an issue.
		if (m_module->getParsing() &&
			m_ptr->findParent<Block *>() == nullptr)
		{
			throw fatal_error("Fell back to alternative get next, but no "
							  "parent was found.");
		}
#endif
		
		// We search through the nearest parent block, so if there aren't
    	// any more parent blocks, there's nothing next.
    	auto block = m_ptr->findParent<Block *>();
    	if (block == nullptr)
    	{
    		return false;
    	}
	
    	// If we're not searching the whole tree and we've already
    	// given one, then there's nothing next.
    	if (m_step > 0 && m_settings.searchWholeTree == false)
    	{
    		return false;
    	}
    	
    	return true;	
	}

}

const Block* Module::BlockIterator::getNext()
{
	if (hasNext() == false)
	{
		return nullptr;
	}
	
	m_step++;
	
	// There is a chance that while in parsing mode,
	// m_ptr is NOT just the top block. If it IS
	// the top block, we want to get its parent first,
	// which should exist.
	if (useContextStack())
	{
		m_ptr = m_ctx_stack.top();
		m_ctx_stack.pop();
		
		return (Block *)m_ptr;
	}
	else
	{
#ifdef DEBUG_BUILD
		// If we fell back here but there's no next,
		// there's an issue.
		if (m_module->getParsing() &&
			m_ptr->findParent<Block *>() == nullptr)
		{
			throw fatal_error("Fell back to alternative get next, but no "
							  "parent was found.");
		}
#endif
		
    	m_ptr = m_ptr->findParent<Block *>();
    	return (Block *)m_ptr;
	}
	

}

const ASTNode* Module::BlockIterator::getLimit() const
{
	if (m_settings.includeLimit == false)
	{
		return nullptr;
	}
	
	// There are no limits when in parsing mode.
	if (m_module->getParsing() == true)
	{
		return nullptr;
	}
	
	const ASTNode* limit = m_ptr;
	auto block = m_ptr->findParent<Block *>();
	
	while (limit != nullptr)
	{
		if (limit->getParent() == block)
		{
			break;
		}
		
		limit = limit->getParent();
	}
	
	return limit;
}

Module::BlockIterator::BlockIterator(const Module* mod, const ASTNode* from,
									 const SearchSettings& settings)
: m_module(mod), m_ptr(from), m_settings(settings)
{
	assertExists(mod, "BlockIterator created without a module");
	assertExists(m_ptr, "BlockIterator created without a from");
	
	if (m_module->getParsing())
	{
		m_ctx_stack = mod->m_ctx;
	}
	
	m_step = 0;
}

llvm::Module* Module::getLLVMModule() const
{
	return m_llvm_module;
}

llvm::IRBuilder<>* Module::getIRBuilder() const
{
	return m_ir_builder;
}

llvm::LLVMContext& Module::getLLVMContext() const
{
	return llvm::getGlobalContext();
}

std::string Module::getFile() const
{
	return m_file;
}

Builder* Module::getBuilder() const
{
	return m_builder;
}

Namespace* Module::getNamespace() const
{
	return m_namespace;
}

void Module::parse()
{
	extern FILE* yyin;
	extern int yyparse(Module* mod);
	extern int yyonce;
	extern void yyflushbuffer();
	
#if defined(DEBUG_BUILD) && YYDEBUG 
	extern int yydebug;
	yydebug = 1;
#endif
	

	if (llvm::sys::fs::is_directory(llvm::Twine(getFile())) == true)
	{
		throw file_error(this);
	}

	auto file = fopen(getFile().c_str(), "r");
	if (file == nullptr)
	{
		throw file_error(this);
	}

	yyflushbuffer();
	yyonce = 0;
	yyin = file;
	
	m_parsing = true;
	yyparse(this);
	m_parsing = false;

	fclose(file);
}

Block* Module::getBlock() const
{
	if (m_ctx.size() == 0)
	{
		throw fatal_error("no blocks have been added to the module");
	}

	return m_ctx.top();
}

Function* Module::getMain() const
{
	return m_main;
}

bool Module::getParsing() const
{
	return m_parsing;
}

void Module::pushBlock(Block *block)
{
	if (block == nullptr)
	{
		throw fatal_error("block must not be nullptr");
	}

	m_ctx.push(block);
}

Block* Module::popBlock()
{
	if (m_ctx.size() == 0)
	{
		throw fatal_error("no blocks have been added to the module");
	}

	auto popped = m_ctx.top();
	m_ctx.pop();
	return popped;
}

void Module::initialize(ASTNode *node)
{
	auto it = std::find(this->m_initialized.begin(), this->m_initialized.end(),
						node);
	
	if (it == std::end(this->m_initialized))
	{
		this->m_initialized.push_back(node);
		node->initialize();
	}
	
	for (auto child : node->getChildren())
	{
		initialize(child);
	}
}

void Module::findDependencies(ASTNode *node)
{
	// Only find the dependencies of a non-generic node.
	if (node->is<Genericable *>() == true &&
		node->as<Genericable *>()->isGeneric())
	{
		return;
	}

	for (auto child : node->getChildren())
	{
		findDependencies(child);
	}

	// Find the dependencies of this node after searching all the children.
	auto it = std::find(this->m_searched.begin(), this->m_searched.end(),
						node);

	if (it == std::end(this->m_searched))
	{
		this->m_searched.push_back(node);
		node->findDependencies();
	}
}

void Module::findDependencies()
{
	findDependencies(getMain());
}

void Module::resolveDependencies(ASTNode *node)
{
	// Go through each of the dependencies and resolve them.
	for (auto dependency : node->getDependencies())
	{
		resolveDependencies(dependency);
	}

	// Resolve this node after resolving the dependencies.
	auto it = std::find(this->m_resolved.begin(), this->m_resolved.end(),
						node);

	if (it == std::end(this->m_resolved))
	{
		this->m_resolved.push_back(node);
		node->resolve();
	}
}

void Module::resolve(ASTNode *node)
{
	// First, resolve the dependencies of this node.
	// This node will also be resolved.
	resolveDependencies(node);

	// Then, resolve the remaining children.
	if (node->is<Genericable *>() == false ||
		node->as<Genericable *>()->isGeneric() == false)
	{
		for (auto child : node->getChildren())
    	{
    		resolve(child);
    	}
	}
}

void Module::process(ASTNode *node)
{
	initialize(node);
	findDependencies(node);
	resolve(node);
}

void Module::initialize()
{
	initialize(getMain());
}

void Module::resolve()
{
	resolve(getMain());
}

void Module::build()
{
	getMain()->build();
	
	// Optimize the module 
	llvm::legacy::PassManager MPM;
	
	MPM.add(llvm::createVerifierPass(true));
	MPM.add(llvm::createBasicAliasAnalysisPass());
	MPM.add(llvm::createPromoteMemoryToRegisterPass());
	MPM.add(llvm::createInstructionCombiningPass());
	MPM.add(llvm::createReassociatePass());
	MPM.add(llvm::createGVNPass());
	MPM.add(llvm::createCFGSimplificationPass());
		
	MPM.run(*m_llvm_module);
}

std::string Module::compile()
{
	auto suffix = "o";
#ifdef _WIN32
	suffix = "obj";
#endif

	// Get the file
	std::error_code ec;
	auto path = getTempFile("module", suffix);
	llvm::raw_fd_ostream raw(path, ec, llvm::sys::fs::OpenFlags::F_RW);

	if (ec)
	{
		throw fatal_error(ec.message());
	}

	llvm::formatted_raw_ostream strm(raw);

	auto pm = new llvm::legacy::PassManager;
	pm->add(new llvm::DataLayoutPass());

	auto emission = llvm::LLVMTargetMachine::CGFT_ObjectFile;

	bool err = getBuilder()->getTargetMachine()->addPassesToEmitFile(*pm, strm,
		emission, false);
	if (err == true)
	{
		throw fatal_error("could not emit file");
	}

	pm->run(*getLLVMModule());
	strm.flush();
	raw.flush();
	raw.close();
	
	delete pm;

	return path;
}

ASTNode* Module::getLatestNode() const
{
	if (getBlock()->getStatements().size() == 0)
	{
		return getBlock();
	}
	else
	{
		return getBlock()->getChildren().back();
	}
}

bool Module::hasNamed(OString name, const ASTNode *from,
					  SearchSettings settings) const
{
	assertExists(from, "From cannot be nullptr");
	
	BlockIterator it(this, from, settings);
	while (it.hasNext())
	{
		// Get the limit from the current element of it.
		const ASTNode* limit = it.getLimit();
		
		if (it.getNext()->hasNamed(name, limit, settings))
		{
			return true;
		}
	}
	
	
	return false;
}

Named* Module::findNamed(OString name, const Type *type, const ASTNode *from,
					   SearchSettings settings) const
{
	BlockIterator it(this, from, settings);
	while (it.hasNext())
	{
		// Get the limit from the current element of it.
		const ASTNode* limit = it.getLimit();
		
		auto named = it.getNext()->getNamed(name, type, limit, settings);
		if (named != nullptr)
		{
			return named;
		}
	}
	
	return nullptr;
}

std::vector<Named*> Module::findAllNamed(OString name, const ASTNode *from)
const
{
	std::vector<Named *> matches;
	
	SearchSettings settings;
	settings.createGeneric = false;
	settings.forceTypeMatch = false;
	settings.includeLimit = true;
	settings.searchWholeTree = true;
	
	BlockIterator it(this, from, settings);
	while (it.hasNext())
	{
		// Get the limit from the current element of it.
		const ASTNode* limit = it.getLimit();
		
		auto found = it.getNext()->getAllNamed(name, limit);
		matches.insert(matches.end(), found.begin(), found.end());
	}
	
	return matches;
}

void Module::addChild(ASTNode *child)
{
	auto it = std::find(m_children.begin(), m_children.end(), child);
	if (it == m_children.end())
	{
		m_children.push_back(child);
		child->m_module = this;
	}
}

void Module::beginCopy()
{
	m_copy_levels++;
}

void Module::defineCopy(const ASTNode *original, const ASTNode *copy)
{
	if (m_copy_levels == 0)
	{
		throw fatal_error("Not in a copy state");
	}
	
	auto it = m_copy_states.find(original);
	if (it != m_copy_states.end())
	{
		throw fatal_error("Redefining a copy mapping");
	}
	
	m_copy_states[original] = copy;
}

bool Module::hasCopy(const ASTNode *original)
{
	if (m_copy_levels == 0)
	{
		throw fatal_error("Not in a copy state");
	}
	
	auto it = m_copy_states.find(original);
	if (it != m_copy_states.end())
	{
		return true;
	}
	
	return false;
}

ASTNode* Module::getCopy(const ASTNode *original)
{
	if (m_copy_levels == 0)
	{
		throw fatal_error("Not in a copy state");
	}
	
	auto it = m_copy_states.find(original);
	if (it != m_copy_states.end())
	{
		return (ASTNode *)it->second;
	}
	
	throw fatal_error("Copy mapping not found");
}

void Module::endCopy()
{
	if (m_copy_levels == 0)
	{
		throw fatal_error("copy state stack is empty");
	}
	
	if (--m_copy_levels == 0)
	{
		m_copy_states.clear();
	}
}

Module::Module()
{
	m_namespace = new Namespace("local");
	m_file = "";
	
	m_llvm_module = new llvm::Module(m_file, getLLVMContext());
	m_ir_builder = new IRBuilder(getLLVMContext());
	
	m_main = new MainFunction(this, "_main");
	
	auto mainFunctionTy = FunctionType::get(this, IntType::get(this, 32),
											std::vector<const Type*>());
	getMain()->setType(mainFunctionTy);
	
	pushBlock(m_main);
}

Module::Module(Builder* builder, std::string filePath)
{
	if (builder == nullptr)
	{
		throw fatal_error("builder must not be null");
	}

	m_builder = builder;
	m_namespace = new Namespace("local");
	m_file = filePath;

	m_llvm_module = new llvm::Module(m_file, getLLVMContext());

	auto target = getBuilder()->getTargetMachine();
	auto triple = target->getTargetTriple();
	auto layout = target->getSubtargetImpl()->getDataLayout();

	m_llvm_module->setTargetTriple(triple);
	m_llvm_module->setDataLayout(layout);

	m_ir_builder = new IRBuilder(getLLVMContext());

	m_main = new MainFunction(this, "_main");

	auto mainFunctionTy = FunctionType::get(this, IntType::get(this, 32),
											std::vector<const Type*>());
	getMain()->setType(mainFunctionTy);


	pushBlock(m_main);

	parse();
	
	if (m_ctx.size() != 1 || getBlock() != m_main)
	{
		throw fatal_error("Parsing didn't clean up blocks!");
	}
}

bool Module::isDefinedTypeName(OString name) const
{
	SearchSettings settings;
	settings.createGeneric = false;
	
	// There's no reason to include a limit as there are no nodes past
	// getLatestNode(), and we want to be able to include getLatestNode()
	// in the search.
	settings.includeLimit = false;
	
	settings.filter = [](Named *named) -> bool
	{
		return named->is<TypeProvider *>();
	};
	
	auto defined = hasNamed(name, getLatestNode(), settings);
	
	if (defined == false && m_parsing)
	{
		// If we didn't find one, let's see if we can
		// look up the context stack.
		auto ctx_copy = m_ctx;
		while (ctx_copy.empty() == false)
		{
			auto block = ctx_copy.top();
			
			if (block->is<Named *>() &&
				block->as<Named *>()->matchesName(name) &&
				block->is<TypeProvider *>())
			{
				return true;
			}
			
			ctx_copy.pop();
		}
		
	}
	
	return defined;
}

Module::~Module()
{
	delete m_ir_builder;
	delete m_main;
	
	for (auto child : m_children)
	{
		delete child;
	}
	
	Type::clear(this);
}
