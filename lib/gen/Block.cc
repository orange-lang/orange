#include "gen/Block.h"
#include "gen/generator.h"
#include "gen/ReturnExpr.h"

Type* Block::getReturnType() {
	Type *ret; 

	auto oldSymtab = CG::Symtab;
	CG::Symtab = symtab;

	for (auto stmt : statements) {
	  if (dynamic_cast<ReturnExpr*>(stmt)) {
	  	ReturnExpr *RE = (ReturnExpr *)stmt;
	  	if (RE->expr == nullptr) {
				CG::Symtab = oldSymtab;
	  		return nullptr;
	  	}

	  	ret = ((ReturnExpr *)stmt)->expr->getType();
			CG::Symtab = oldSymtab;	  	
	  	return ret; 
	  }
	}

	CG::Symtab = oldSymtab;
	return nullptr;
}

Value* Block::Codegen() {
	for (Statement *stmt : statements) {
		stmt->Codegen();

	  if (dynamic_cast<ReturnExpr*>(stmt)) {
	  	break; // only process one return statement per block. 
	  	// anything else is unreachable.
	  }
	}



	return nullptr;
}
