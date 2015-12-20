/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Type.h"

class PointerType : public Type
{
private:
	const Type* m_contained = nullptr;

protected:
	PointerType(const Type* contained, bool isConst);
	
public:
	virtual std::string getString() const override;
	virtual std::string getSignature() const override;
	
	virtual bool isSigned() const override;
	
	virtual bool isPointerTy() const override;
	
	virtual const Type* getBaseTy() const override;
	
	virtual const Type* getRootTy() const override;
	
	virtual const Type* getConst() const override;
	
	virtual bool matches(const Type* ty) const override;
	
	virtual llvm::Type* getLLVMType() const override;
	
	static PointerType* get(Module* mod, const Type* contained, bool isConst = false);
};