#include "gen/Block.h"
#include "gen/generator.h"
#include "gen/IfStatement.h"
#include "gen/FunctionStatement.h"
#include "gen/ReturnExpr.h"
#include "gen/ForLoop.h"

std::string Block::string() {
	std::stringstream ss;

	CG::Symtabs.push(symtab);

	for (Statement *s : statements) {
		if (s == nullptr) continue;
		ss << s->string() << std::endl;
	}

	CG::Symtabs.pop();

	return ss.str();
}

Block* Block::clone() { 
	Block* ret = new Block();
	ret->symtab = symtab->clone();
	CG::Symtabs.push(ret->symtab);
	for (Statement *stmt : statements) 
		ret->statements.push_back((Statement *)stmt->clone());
	CG::Symtabs.pop();
	return ret;
}

bool Block::hasReturnStatement() {
	for (auto stmt : statements) {
		if (stmt->getClass() == "ReturnExpr") 
			return true; 
	}
	
	return false; 
}

bool Block::hasJmpInstr() {
	for (auto stmt : statements) {
		if (stmt->getClass() == "ReturnExpr" || stmt->getClass() == "BreakStatement" ||
				stmt->getClass() == "ContinueStatement") 
		{ 
			return true; 
		}
	}
	
	return false; 	
}

Type* Block::getLastStatementType() {
	Type *ret = nullptr; 

	CG::Symtabs.push(symtab);

	if (statements.size() > 0 && statements.back()->getClass() != "FunctionStatement" &&
		statements.back()->getClass() != "ExternFunction") {
		ret = statements.back()->getType();
	}

	CG::Symtabs.pop();
	return ret;
}


Type* Block::getReturnType() {
	Type *ret; 

	CG::Symtabs.push(symtab);
	std::string currFunction = CG::Symtabs.top()->getFunctionName();

	for (auto stmt : statements) {
		if (stmt->getClass() == "ReturnExpr") {
	  	ReturnExpr *RE = (ReturnExpr *)stmt;
	  	if (RE->expr == nullptr) {
				CG::Symtabs.pop();
	  		return nullptr;
	  	}

	  	Expression *expr = ((ReturnExpr *)stmt)->expr;
	  	ret = expr->getType();

	  	if (ret) {
	  		CG::Symtabs.pop();
		  	return ret; 
	  	}
		}

		if (stmt->getClass() == "IfStatement") {
			// call Block::getReturnType on all blocks in the IfStatement, returning the first non null one. 
			IfStatement *ifstmt = (IfStatement*)stmt;
			for (Block *b : ifstmt->blocks) {
				Type *t = b->getReturnType();
				if (t) {
					CG::Symtabs.pop();
					return t; 
				}
			}
		}

		if (stmt->getClass() == "ForLoop") {
			ForLoop *loop = (ForLoop*)stmt;
			Type *t = loop->body->getReturnType();
			if (t) {
				CG::Symtabs.pop();
				return t;
			}
		}
	}

	CG::Symtabs.pop();
	return nullptr;
}

void Block::resolve() {
	if (resolved) 
		return;
	resolved = true;

	if (symtab == nullptr) {
		std::cerr << "fatal: block does not have an assigned symbol table.\n";
		exit(1);
	}

	CG::Symtabs.push(symtab);

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

	CG::Symtabs.pop();
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

Block::~Block() {
	for (auto stmt : statements) {
		delete stmt; 
	}

	delete symtab;
}