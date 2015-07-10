/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_ENUM_STMT_H__
#define __ORANGE_ENUM_STMT_H__

#include "AST.h"
#include "Values.h"

struct EnumPair {
public: 
	std::string name = ""; 
	BaseVal* value = nullptr; 

	EnumPair() {}
	EnumPair(std::string name) : name(name) {}
	EnumPair(std::string name, BaseVal* value) : name(name), value(value) {}
}; 

class EnumStmt : public Statement {
private:
	std::string m_name;

	std::vector<EnumPair> m_enums;
	BaseVal* m_last_val = nullptr;
public:
	virtual std::string getClass() { return "EnumStmt"; }

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual std::string string();

	virtual std::string name() const { return m_name; }

	virtual void resolve();

	virtual void addEnum(std::string name);

	virtual void addEnum(std::string name, BaseVal* value);

	virtual bool isSigned();

	virtual BaseVal* getEnumValue(std::string name);

	EnumStmt(std::string name);
}; 

#endif 