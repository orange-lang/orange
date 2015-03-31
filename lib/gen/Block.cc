#include "gen/Block.h"
#include "gen/generator.h"
#include "gen/IfStatement.h"
#include "gen/ReturnExpr.h"

Type* Block::getReturnType() {
	Type *ret; 

	auto oldSymtab = CG::Symtab;
	CG::Symtab = symtab;

	for (auto stmt : statements) {
		if (stmt->getClass() == "ReturnExpr") {
	  	ReturnExpr *RE = (ReturnExpr *)stmt;
	  	if (RE->expr == nullptr) {
				CG::Symtab = oldSymtab;
	  		return nullptr;
	  	}

	  	Expression *expr = ((ReturnExpr *)stmt)->expr;
	  	ret = expr->getType();

			CG::Symtab = oldSymtab;	  	
	  	return ret; 
		}

		if (stmt->getClass() == "IfStatement") {
			// call Block::getReturnType on all blocks in the IfStatement, returning the first non null one. 
			IfStatement *ifstmt = (IfStatement*)stmt;
			for (Block *b : ifstmt->blocks) {
				Type *t = b->getReturnType();
				if (t) {
					CG::Symtab = oldSymtab;	  	
					return t; 
				}
			}
		}
	}

	CG::Symtab = oldSymtab;
	return nullptr;
}

Value* Block::Codegen() {
	Value *ret = nullptr; 
	for (Statement *stmt : statements) {
		if (stmt == nullptr) {
			std::cerr << "fatal: generating a null statement\n";
		}

		DEBUG_MSG("(BLOCK) CALLING CODEGEN FOR " << stmt->getClass());
		ret = stmt->Codegen();


		if (stmt->getClass() == "VarExpr" || stmt->getClass() == "IfStatement") {
			if (ret) ret = CG::Builder.CreateLoad(ret);
		} 
		
	  if (dynamic_cast<ReturnExpr*>(stmt)) {
	  	break; // only process one return statement per block. 
	  	// anything else is unreachable.
	  }
	}

	return ret;
}
