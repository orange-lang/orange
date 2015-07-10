/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/IfStmts.h>
#include <orange/CondBlock.h>
#include <orange/generator.h>
#include <helper/string.h>

std::string IfStmts::string() {
	std::stringstream ss; 

	// Very first block is always an if statement. 
	for (unsigned int i = 0; i < m_blocks.size(); i++) {
		auto block = m_blocks[i];

		if (block->getClass() == "CondBlock") {
			CondBlock* condBlock = (CondBlock*)block;

			if (i != 0) ss << "else ";
			ss << "if " << condBlock->condition()->string() << ":\n";

			std::vector<std::string> lines = split(condBlock->string(), '\n');
			for (std::string line : lines) {
				ss << "\t" << line << std::endl;
			}
		} else {
			ss << "else:\n"; 

			std::vector<std::string> lines = split(block->string(), '\n');
			for (std::string line : lines) {
				ss << "\t" << line << std::endl;
			}
		}
	}

	return ss.str();
}

Value* IfStmts::Codegen() {
	std::vector<BasicBlock*> BBs;

	// Get our function to use during generation
	auto curFunction = (FunctionStmt*)GE::runner()->symtab()->findStructure("FunctionStmt");
	auto llvmFunction = (Function *)curFunction->getValue();

	// Each block has two BasicBlocks: a check and a trueBlock. 
	for (auto block : m_blocks) {
		BBs.push_back(BasicBlock::Create(GE::runner()->context(), "check", llvmFunction, curFunction->getBlockEnd()));
		BBs.push_back(BasicBlock::Create(GE::runner()->context(), "trueBlock", llvmFunction, curFunction->getBlockEnd()));
	}

	// add our continue block
	auto continueBlock = BasicBlock::Create(GE::runner()->context(), "continue", llvmFunction, curFunction->getBlockEnd());
	BBs.push_back(continueBlock);

	// Jump to our initial block.
	GE::builder()->CreateBr(BBs[0]);

	// then, for each block:
	//		- if it's a conditional block, check for conditional, and do conditional jump to corresponding block
	// 		- if it's not a conditional block (else), do jump to corresponding block 
	for (unsigned int i = 0; i < m_blocks.size(); i++) {
		auto checkBlock = BBs[(i * 2) + 0];
		auto trueBlock  = BBs[(i * 2) + 1];
		auto nextCheck  = BBs[(i * 2) + 2];
		auto genBlock   = m_blocks[i];

		GE::builder()->SetInsertPoint(checkBlock);

		if (genBlock->getClass() == "CondBlock") {
			CondBlock* condBlock = (CondBlock*)genBlock; 
			auto condition = condBlock->CodegenCondition();

			if (condBlock->condition()->returnsPtr()) {
				condition = GE::builder()->CreateLoad(condition);
			}

			// Our condition must be a boolean, try casting it if we can...
			if (CastingEngine::CastValueToType(&condition, IntTy::getUnsigned(1), condBlock->condition()->isSigned(), true) == false) {
				throw CompilerMessage(*(condBlock->condition()), "could not cast to boolean!");
			}

			if (condBlock->inverted()) {
				condition = GE::builder()->CreateNot(condition);
			}

			GE::builder()->CreateCondBr(condition, trueBlock, nextCheck);
		} else {
			// Go right to our true block
			GE::builder()->CreateBr(trueBlock);
		}

		// Now, set our insert point to the true block and codegen it.
		// If the Block doesn't have a return, jump to continue after wards.
		GE::builder()->SetInsertPoint(trueBlock);
	
		genBlock->Codegen();
		
		if (genBlock->hasJump() == false) {
			GE::builder()->CreateBr(continueBlock);
		}
	}
	
	GE::builder()->SetInsertPoint(continueBlock);

	return nullptr;
}

ASTNode* IfStmts::clone() {
	IfStmts* clone = new IfStmts; 
	for (auto block : m_blocks) {
		clone->addBlock((Block *)block->clone());
	}
	
	clone->copyProperties(this);
	return clone; 
}

void IfStmts::resolve() {
	// If we're not already locked, we should be locked now; 
	// don't allow adding any more blocks.
	m_locked = true; 

	ASTNode::resolve();
}

void IfStmts::addBlock(Block* block) {
	if (m_locked == true) {
		throw std::runtime_error("addBlock: IfStmts already locked!");
	}

	// We only allow Blocks and CondBlocks to be added to if statements. 
	// Functions inherit from Block and we don't want those to be 
	// added here.
	if (block->getClass() != "Block" && block->getClass() != "CondBlock") {
		throw std::runtime_error("addBlock: block is invalid!");
	}

	block->setParent(this);
	m_blocks.push_back(block);

	// If we're adding in a Block, this is considered an "else"
	// statement, so we shouldn't allow any more blocks to be 
	// added.  
	if (block->getClass() == "Block") {
		m_locked = true; 
	}

	addChild(block);
}
