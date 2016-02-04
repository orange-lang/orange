/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include "Type.h"

class Expression;

namespace Orange { class VariadicArrayType; }

class Orange::VariadicArrayType : public Orange::Type
{
private:
	const Type* m_contained = nullptr;
	Expression* m_size = nullptr;
protected:
	VariadicArrayType(const Type* contained, Expression* size, bool isConst);
public:
	static std::string getSignature(const Type* conatined, Expression* size,
									bool isConst);
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	Expression* getSize() const;
	
	virtual bool isSigned() const override;
	
	virtual bool isArrayTy() const override;
	
	virtual const Type* getBaseTy() const override;
	
	virtual const Type* getRootTy() const override;
	
	virtual const Type* getConst() const override;
	
	virtual bool isVariadiclySized() const override;
	
	virtual std::vector<Expression*> getVariadicSizes() const override;
	
	virtual const Type* copyType() const override;
	
	static VariadicArrayType* get(Module* mod, const Type* contained,
								  Expression* expr, bool isConst = false);
};