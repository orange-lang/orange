/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Type.h"

class Expression;

class VariadicArrayType : public Type
{
private:
	Type* m_contained = nullptr;
	Expression* m_size = nullptr;
protected:
	VariadicArrayType(Type* contained, Expression* size, bool isConst);
public:
	static std::string getSignature(Type* conatined, Expression* size,
									bool isConst);
	virtual std::string getSignature() const override;
	
	Expression* getSize() const;
	
	virtual bool isSigned() const override;
	
	virtual bool isArrayTy() const override;
	
	virtual Type* getBaseTy() const override;
	
	virtual Type* getRootTy() const override;
	
	virtual Type* getConst() const override;
	
	static VariadicArrayType* get(Type* contained, Expression* expr,
								  bool isConst = false);
};