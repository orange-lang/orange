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
#include <tuple>
#include <typeinfo>

class Module;

namespace llvm { class Type; }
namespace llvm { class LLVMContext; }
namespace llvm { class Value; }

typedef enum {
	INT8,
	INT16,
	INT32,
	INT64,
	UINT8,
	UINT16,
	UINT32,
	UINT64,
	FLOAT,
	DOUBLE,
	VOID,
	OTHER
} BasicType;

class Type;
typedef std::tuple<size_t, size_t> TypeTuple;
typedef std::function<int(Type*,Type*)> TypeCallback;

const int NO_CAST = 0;

/**
 * Type is the base class for any Orange Type.
 */
class Type {
private:
	static std::map<std::string, Type *> m_defined;
	static std::map<TypeTuple, int> m_cast_map;
	static std::map<TypeTuple, TypeCallback> m_cast_func_map;
protected:
	llvm::Type* m_type = nullptr;
	llvm::LLVMContext* m_context = nullptr;
	
	static Type* getDefined(std::string signature);
	static void define(std::string signature, Type* ty);
	
	static void defineCast(const std::type_info& from, const std::type_info& to, int cast);
	void defineCast(const std::type_info& to, int cast);
	void defineCast(const std::type_info& to, TypeCallback cb);
	
	Type();
public:
	virtual bool isSigned() const;
	
	/// Determines whether or not type is plain (int, float, not a pointer).
	virtual bool isPODTy() const;
	virtual bool isArrayTy() const;
	virtual bool isDoubleTy() const;
	virtual bool isFloatTy() const;
	virtual bool isFloatingPointTy() const;
	virtual bool isFunctionTy() const;
	virtual bool isIntTy() const;
	virtual bool isPointerTy() const;
	virtual bool isVoidTy() const;
	
	/// Gets plain old data type. 
	virtual BasicType PODTy() const;
	
	Type* getPointerTo();
	
	/// Gets the contained type, or this
	virtual Type* getBaseTy();
	
	/// Gets the root type.
	virtual Type* getRootTy();
	
	virtual std::string getSignature() const;
	
	/// Gets the cast operation to convert to another type.
	int castOperation(Type* to);
	
	llvm::Type* getLLVMType() const;
	
	virtual ~Type();
};
