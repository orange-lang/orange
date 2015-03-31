#include "gen/IfStatement.h"
#include "gen/Block.h"
#include "gen/CondBlock.h"
#include "gen/generator.h"

void IfStatement::resolve() {
	if (resolved)
		return;

	resolved = true;

	for (Block *b : blocks) {
		if (dynamic_cast<CondBlock*>(b)) {
			CondBlock *cb = (CondBlock *)b;
			cb->condition->resolve();
		}

		b->resolve();
	}

}

Value* IfStatement::Codegen() {
	// first, create blocks for all the blocks 
	std::vector<BasicBlock *> BBs;
	for (Block *b : blocks) {
		BBs.push_back(BasicBlock::Create(getGlobalContext(), "check", CG::Symtab->getFunction(), CG::Symtab->getFunctionEnd()));
		BBs.push_back(BasicBlock::Create(getGlobalContext(), "truebr", CG::Symtab->getFunction(), CG::Symtab->getFunctionEnd()));
	} 

	// create a block that all blocks continue to (including the main block)
	BBs.push_back(BasicBlock::Create(getGlobalContext(), "continue", CG::Symtab->getFunction(), CG::Symtab->getFunctionEnd()));

	// allocate a variable for this to return to, IF this has a type.
	Value *retVal = nullptr; 
	Type *ty = getType();

	if (ty->isVoidTy() == false) {
		retVal = CG::Builder.CreateAlloca(ty);
	}

	// then, for each block:
	//		- if it's a conditional block, check for conditional, and do conditional jump to corresponding block
	// 		- if it's not a conditional block (else), do jump to corresponding block 
	CG::Builder.CreateBr(BBs[0]);

	for (int i = 0; i < blocks.size(); i++) {
		int BBi = (i*2)+1; // this will point to truebr for this block 
		CG::Builder.SetInsertPoint(BBs[BBi-1]);

		if (dynamic_cast<CondBlock*>(blocks[i])) {
			CondBlock *b = (CondBlock *)blocks[i];
			Value *cond = b->condition->Codegen();

			if (cond->getType()->isIntegerTy(1) == false) {
				std::cerr << "fatal: must use a boolean value as the condition in an if statement.\n";
				exit(1);
			}

			// if it's true, jump to the created BB
			// if it's false, jump forward to the next conditional check.
			CG::Builder.CreateCondBr(cond, BBs[BBi], BBs[BBi+1]);

			continue; 
		}		

		// Jump to BBs[BBi]
		CG::Builder.CreateBr(BBs[BBi]);

		Block *b = (Block *)blocks[i];
	}

	// next, for each truebr block:
	for (int i = 0; i < blocks.size(); i++) {
		// 1. set up insert point to appropriate basicblock
		int BBi = (i*2)+1; // this will point to truebr for this block 
		CG::Builder.SetInsertPoint(BBs[BBi]);

		// 2. set up scope for that block
		auto oldSymtab = CG::Symtab;
		CG::Symtab = blocks[i]->symtab;

		// 3. codegen that block.
		Value *blockRet = blocks[i]->Codegen();

		if (retVal != nullptr) {
			CG::Builder.CreateStore(blockRet, retVal);
		}

		// 4. does the block contain a return statement?
		bool hasReturn = false; 
		for (Statement *stmt : blocks[i]->statements) {
			if (stmt->getClass() == "ReturnExpr") {
				hasReturn = true; 
				break; 
			}
		}

		// 5. set up jump to continue block if there's no return
		if (hasReturn == false) 
			CG::Builder.CreateBr(BBs[BBs.size()-1]);

		// 6. Restore symtab
		CG::Symtab = oldSymtab;
	}

	// set insert point to continue block
	CG::Builder.SetInsertPoint(BBs[BBs.size()-1]);

	return retVal; 
}

Type *IfStatement::getType() {
	// Go through each block, checking the value of the last statement.	
	// All types must match. If they don't match, the type of the if statement 
	// is null, and can't be used as an expression. 
	Type *ret = nullptr;
	for (Block *b : blocks) {
		Type *t = b->getLastStatementType();

		if (ret == nullptr) {
			ret = t; 
			continue; 
		}

		if (ret->getTypeID() != t->getTypeID()) {
			return Type::getVoidTy(getGlobalContext());
		}
	}

	return ret;
}	

