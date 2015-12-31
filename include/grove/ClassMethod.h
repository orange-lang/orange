/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Function.h"
#include "ClassTopLevel.h"
#include "Protectable.h"
#include "Staticable.h"

class ClassDecl;
class BinOpAssign;
class MemberVarDecl;

/**
 * Represents a method for a class.
 * Provides a hint that is the this parameter.
 */
class ClassMethod : public Function, public ClassTopLevel, public Protectable,
    public Staticable
{
private:
	ClassDecl* m_class = nullptr;
	Parameter* m_this_param = nullptr;
	
protected:
	void addThisParam();
public:
	virtual bool usableFrom(const ASTNode* from) const override;
	
	virtual ProtectionLevel defaultProtectionLevel() const override;
	
	virtual void initialize() override;
	
	virtual void findDependencies() override;
	
	virtual bool isConstructor() const;
	
	virtual ASTNode* copy() const override;
	
	virtual std::vector<ObjectBase**> getMemberNodes() override;
	
	virtual std::vector<std::vector<ObjectBase *>*> getMemberLists() override;
	
	BinOpAssign* getInitializerForMember(MemberVarDecl *member) const;
	
	Parameter* getThisParam() const;
	
	ClassMethod(OString name, ClassDecl* theClass,
				std::vector<Parameter *> params);
	ClassMethod(const ClassMethod& other);
};