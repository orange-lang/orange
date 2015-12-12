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
	auto ptr = from;
	
	while (ptr != nullptr)
	{
		// Find the nearest block from this pointer.
		auto block = ptr->findParent<Block *>();
		
		if (block == nullptr)
		{
			break;
		}
		
		const ASTNode* limit = nullptr;
		
		if (settings.includeLimit)
		{
			// Find closest node whose parent is that block.
			limit = ptr;
			while (limit != nullptr)
			{
				if (limit->getParent() == block)
				{
					break;
				}
				
				limit = limit->getParent();
			}
		}
		
		if (block->hasNamed(name, limit, settings))
		{
			return true;
		}
		
		if (settings.searchWholeTree == false)
		{
			break;
		}
		else
		{
			// If we didn't find one, start looking from the block.
			ptr = block;
		}
	}
	
	return false;
}

Named* Module::findNamed(OString name, Type *type, const ASTNode *from,
					   SearchSettings settings) const
{
	auto ptr = from;
	
	while (ptr != nullptr)
	{
		// Find the nearest block from this pointer.
		auto block = ptr->findParent<Block *>();
		
		if (block == nullptr)
		{
			break;
		}
		
		const ASTNode* limit = nullptr;
		
		if (settings.includeLimit)
		{
			// Find closest node whose parent is that block.
			limit = ptr;
			while (limit != nullptr)
			{
				if (limit->getParent() == block)
				{
					break;
				}
				
				limit = limit->getParent();
			}
		}
		
		auto named = block->getNamed(name, type, limit, settings);
		if (named != nullptr)
		{
			return named;
		}
		
		if (settings.searchWholeTree == false)
		{
			break;
		}
		else
		{
			// If we didn't find it, start looking from the block.
			ptr = block;
		}
	}
	
	return nullptr;
}

std::vector<Named*> Module::findAllNamed(OString name, const ASTNode *from)
const
{
	std::vector<Named *> matches;
	
	auto ptr = from;
	while (ptr != nullptr)
	{
		// Find the nearest block from this pointer.
		auto block = ptr->findParent<Block *>();
		
		if (block == nullptr)
		{
			break;
		}
		
		// Find closest node whose parent is that block.
		auto limit = ptr;
		while (limit != nullptr)
		{
			if (limit->getParent() == block)
			{
				break;
			}
			
			limit = limit->getParent();
		}
		
		auto found = block->getAllNamed(name, limit);
		matches.insert(matches.end(), found.begin(), found.end());
		
		ptr = block;
	}
	
	return matches;
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

	auto mainFunctionTy = FunctionType::get(IntType::get(32),
											std::vector<Type*>());
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
	
	return hasNamed(name, getLatestNode(), settings);
}

Module::~Module()
{
	delete m_ir_builder;
	delete m_main;
}
