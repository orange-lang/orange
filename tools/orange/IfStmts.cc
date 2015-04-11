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

Value* IfStmts::Codegen() {
	// Our first step is to generate all of the BasicBlocks 
	// that we need. 
	//
	// There's always a "continue" block at the end.
	//
	// Each CondBlock has two BasicBlocks: 
	//		- trueBlock
	//		- falseBlock 
	// 
	std::vector<BasicBlock*> BBs; 

	auto curFunction = (FunctionStmt*)GE::runner()->symtab()->findStructure("FunctionStmt");
	auto llvmFunction = (Function *)curFunction->getValue();

	for (auto block : m_blocks) {
		if (block->getClass() == "CondBlock") {
			// if or elif statement
			auto trueBlock = BasicBlock::Create(GE::runner()->context(), "trueBlock", llvmFunction, curFunction->getBlockEnd()); 
			auto falseBlock = BasicBlock::Create(GE::runner()->context(), "falseBlock", llvmFunction, curFunction->getBlockEnd()); 
			
			BBs.push_back(trueBlock);
			BBs.push_back(falseBlock);
		} else if (block->getClass() == "Block") {
			// else statement 
			auto elseBlock = BasicBlock::Create(GE::runner()->context(), "elseBlock", llvmFunction, curFunction->getBlockEnd()); 
			BBs.push_back(elseBlock);
		}
	}

	auto continueBlock = BasicBlock::Create(GE::runner()->context(), "continueBlock", llvmFunction, curFunction->getBlockEnd()); 
	BBs.push_back(continueBlock);

	bool usingContinue = false; 
	bool hasElse = false;

	// Now that we have all of our BasicBlocks set up, we can generate the code now.
	//
	// At the end of the trueBlock:
	//		- If there's a return statement in the CondBlock, don't do anything.
	//		- Otherwise, jump to the continue block at the end.
	// The false block will either generate another CondBlock or jump to an 
	// else block, if it exists, or jump to the continue block, if nothing else.
	for (int i = 0; i < m_blocks.size(); i++) {
		auto block = m_blocks[i];

		// Every CondBlock has BasicBlocks at (i * 2) and (i * 2) + 1
		// The elseBlock will always be at (i * 2). 
		if (block->getClass() == "CondBlock") {
			auto trueBlock = BBs[(i * 2)];
			auto falseBlock = BBs[(i * 2) + 1];

			CondBlock* condBlock = (CondBlock*)block;

			auto condition = condBlock->CodegenCondition();

			if (condBlock->condition()->returnsPtr()) {
				condition = GE::builder()->CreateLoad(condition);
			}

			// The condition should always be a bool, so cast it now.
			CastingEngine::CastValueToType(&condition, AnyType::getUIntNTy(1), condBlock->condition()->isSigned(), true);

			// Next, create our jump to the blocks.
			GE::builder()->CreateCondBr(condition, trueBlock, falseBlock);

			// Go to the trueBlock and generate the body of our condition 
			GE::builder()->SetInsertPoint(trueBlock);
			condBlock->Codegen();

			// If the condition has a return, don't do anything, otherwise, jump to continue.
			if (condBlock->hasReturn() == false && trueBlock->getTerminator() == nullptr) {
				GE::builder()->CreateBr(continueBlock);
				usingContinue = true;
			}

			GE::builder()->SetInsertPoint(falseBlock); 

			// Are we going to use our falseBlock? If not,
			// jump immediately to continue.
			if (i + 1 >= m_blocks.size() && falseBlock->getTerminator() == nullptr) {
				GE::builder()->CreateBr(continueBlock);
			}

		} else if (block->getClass() == "Block") {
			hasElse = true;

			auto elseBlock = BBs[(i * 2)];
			GE::builder()->CreateBr(elseBlock);

			GE::builder()->SetInsertPoint(elseBlock);
			block->Codegen();

			if (block->hasReturn() == false && elseBlock->getTerminator() == nullptr) {
				GE::builder()->CreateBr(continueBlock);
				usingContinue = true;
			}
		}
	}

	if (hasElse == false || usingContinue == true) {
		GE::builder()->SetInsertPoint(continueBlock);
	} else {
		continueBlock->eraseFromParent();
	}

	return nullptr;
}

ASTNode* IfStmts::clone() {
	IfStmts* clone = new IfStmts; 
	for (auto block : m_blocks) {
		clone->addBlock((Block *)block->clone());
	}
	return clone; 
}

void IfStmts::resolve() {
	if (m_resolved) return;
	m_resolved = true; 

	// If we're not already locked, we should be locked now; 
	// don't allow adding any more blocks.
	m_locked = true; 

	// Resolve all of our blocks.
	for (auto block : m_blocks) {
		block->resolve();
	}
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

	m_blocks.push_back(block);

	// If we're adding in a Block, this is considered an "else"
	// statement, so we shouldn't allow any more blocks to be 
	// added.  
	if (block->getClass() == "Block") {
		m_locked = true; 
	}
}
