#ifndef __SYMTAB_H__ 
#define __SYMTAB_H__
#include "AST.h"

class Symobj {
private:
	Value *m_value = nullptr;
	Type *m_type = nullptr; 
public:
	bool isSigned = false;
	bool isFunction = false;

	Statement *reference = nullptr;
	
	Value *getValue() const;
	Type *getType() const;  

	// Set value with a non-null object will 
	// also set type to the type of value. 
	void setValue(Value *v);

	// If m_value is not null, then calling this will have no effect.  
	void setType(Type *t);

	Symobj() { };
	Symobj(Value *v) { setValue(v); }
	Symobj(Type *t) { setType(t); }
}; 

class SymTable {
public:
	SymTable *parent = nullptr; 
	std::map< std::string, Symobj* > objs;

	Value *retVal = nullptr;
	BasicBlock *FunctionEnd = nullptr; 
	BasicBlock *BlockEnd = nullptr; 
	
	// If Symobj doesn't exist, creates one. 
	void create(std::string name);
	
	Symobj* find(std::string name);

	BasicBlock* getFunctionEnd();
};

#endif