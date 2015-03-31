#include "gen/Block.h"
#include "gen/generator.h"
#include "gen/IfStatement.h"
#include "gen/FunctionStatement.h"
#include "gen/ReturnExpr.h"

std::string Block::string() {
	std::stringstream ss;

	auto oldSymtab = CG::Symtab;
	CG::Symtab = symtab;

	for (Statement *s : statements) {
		if (s == nullptr) continue;
		ss << s->string() << std::endl;
	}

	if (oldSymtab)
		CG::Symtab = oldSymtab;

	return ss.str();
}

bool Block::hasReturnStatement() {
	for (auto stmt : statements) {
		if (stmt->getClass() == "ReturnExpr") 
			return true; 
	}
	
	return false; 
}

Type* Block::getLastStatementType() {
	Type *ret = nullptr; 

	auto oldSymtab = CG::Symtab;
	CG::Symtab = symtab;

	if (statements.size() > 0) {
		ret = statements.back()->getType();
	}

	CG::Symtab = oldSymtab;
	return ret;
}


Type* Block::getReturnType() {
	Type *ret; 

	auto oldSymtab = CG::Symtab;
	CG::Symtab = symtab;

	std::string currFunction = CG::Symtab->getFunctionName();

	for (auto stmt : statements) {
		if (stmt->getClass() == "ReturnExpr") {
	  	ReturnExpr *RE = (ReturnExpr *)stmt;
	  	if (RE->expr == nullptr) {
				CG::Symtab = oldSymtab;
	  		return nullptr;
	  	}

	  	Expression *expr = ((ReturnExpr *)stmt)->expr;
	  	ret = expr->getType();

	  	if (ret) {
				CG::Symtab = oldSymtab;	  	
		  	return ret; 
	  	}
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

void Block::resolve() {
	if (resolved) 
		return;

	resolved = true;

	auto oldSymtab = CG::Symtab;
	CG::Symtab = symtab;

	std::vector<FunctionStatement*> functions;

	for (Statement *stmt : statements) {
		if (stmt == nullptr) {
			std::cerr << "fatal: can't perform semantic analysis on null statement\n"; 
			exit(1); 
		}

		if (stmt->getClass() == "FunctionStatement") {
			FunctionStatement *fstmt = (FunctionStatement *)stmt; 
			functions.push_back(fstmt);
			continue;
		} 

		stmt->resolve();
	}


	for (FunctionStatement *fstmt : functions) {
		if (fstmt == nullptr) {
			std::cerr << "fatal: can't perform semantic analysis on null function statement\n"; 
			exit(1); 
		}

		fstmt->resolve();
	}

	CG::Symtab = oldSymtab;
}

Value* Block::Codegen() {
	Value *ret = nullptr; 

	for (Statement *stmt : statements) {
		if (stmt == nullptr) {
			std::cerr << "fatal: generating a null statement\n";
		}

		DEBUG_MSG("(BLOCK) CALLING CODEGEN FOR " << stmt->getClass() << " ( " << stmt->string() << " )");
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
