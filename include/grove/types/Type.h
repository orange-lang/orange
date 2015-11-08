/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <map>
#include <string>

class Module;

namespace llvm { class Type; }
namespace llvm { class LLVMContext; }

/**
 * Type is the base class for any Orange Type.
 */
class Type {
private:
	static std::map<std::string, Type *> m_defined;
protected:
	llvm::Type* m_type = nullptr;
	llvm::LLVMContext* m_context = nullptr;
	
	static Type* getDefined(std::string signature);
	static void define(std::string signature, Type* ty);
	
	Type();
public:
	virtual bool isSigned() const;
	
	std::string getSignature() const;
	
	llvm::Type* getLLVMType() const; 
};
