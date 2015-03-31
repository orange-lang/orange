#ifndef __SYMTAB_H__ 
#define __SYMTAB_H__
#include "AST.h"

class SymTable;
class ForLoop;

class Symobj {
private:
	friend class SymTable;
	Value *m_value = nullptr;
	Type *m_type = nullptr; 
public:
	bool isSigned = false;
	bool isFunction = false;
	bool isLocked = false;
	bool isConst = false;

	Statement *reference = nullptr;
	
	Value *getValue() const;
	Type *getType() const;  

	// Set value with a non-null object will 
	// also set type to the type of value. 
	void setValue(Value *v);

	// If m_value is not null, then calling this will have no effect.  
	void setType(Type *t);

	Symobj* clone() { 
		Symobj* ret = new Symobj();
		ret->m_value = m_value;
		ret->m_type = m_type; 
		ret->isSigned = isSigned;
		ret->isFunction = isFunction;
		ret->isLocked = isLocked; 
		ret->reference = reference; 
		return ret;
	}

	Symobj() { };
	Symobj(Value *v) { setValue(v); }
	Symobj(Type *t) { setType(t); }

	~Symobj();
}; 

class SymTable {
public:
	SymTable *parent = nullptr; 
	std::map< std::string, Symobj* > objs;

	Value *retVal = nullptr;
	Function *TheFunction = nullptr; 
	std::string* FunctionName = nullptr;
	BasicBlock *FunctionEnd = nullptr; 
	BasicBlock *BlockEnd = nullptr; 
	ForLoop *Loop = nullptr;

	int ID = 0;
	
	// If Symobj doesn't exist, creates one. 
	void create(std::string name);
	
	Symobj* find(std::string name);

	void dump(); 

	SymTable* clone() {
		SymTable* ret = new SymTable();
		ret->parent = parent; 
		for (auto& kv : objs) {
			ret->objs[kv.first] = kv.second->clone();
		}
		ret->retVal = retVal; 
		ret->TheFunction = TheFunction; 
		ret->FunctionName = FunctionName;
		ret->FunctionEnd = FunctionEnd; 
		ret->BlockEnd = BlockEnd; 
		return ret;
	}

	// Searched up symtable until finding TheFunction != nullptr, returns retVal.
	Value *getRetVal();

	std::string getFunctionName();
	Function* getFunction();
	BasicBlock* getFunctionEnd();
	ForLoop* getLoop();

	SymTable();
};

#endif