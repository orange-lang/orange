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

#include "../Comparison.h"
#include "../ObjectBase.h"

class Module;

namespace llvm { class Type; }
namespace llvm { class LLVMContext; }
namespace llvm { class Value; }

/// BasicTypes are plain old data types that are
/// ordered by precedence, descending.
typedef enum {
	DOUBLE = 1,
	FLOAT,
	INT64,
	INT32,
	INT16,
	INT8,
	UINT64,
	UINT32,
	UINT16,
	UINT8,
	UINT1,
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
class Type : public ObjectBase {
private:
	/// The map of defined types, where the key is a unique identifier.
	static std::map<std::string, Type *> m_defined;

	/// The map of type tuples to a cast operation.
	/// Defines a cast operation to cast from tuple.0 to tuple.1.
	static std::map<TypeTuple, int> m_cast_map;

	/// The map of type tuples to a cast operation callback.
	/// Defines a callback that returns a cast operation to cast from
	/// tuple.0 to tuple.1.
	static std::map<TypeTuple, TypeCallback> m_cast_func_map;
protected:
	llvm::Type* m_type = nullptr;
	llvm::LLVMContext* m_context = nullptr;

	/// Gets a type given by a signature, if it is defined.
	/// Returns nullptr otherwise.
	static Type* getDefined(std::string signature);

	/// Defines a type with a given signature.
	/// ty must not be null.
	static void define(std::string signature, Type* ty);

	/// Defines a direct mapping from a type to an operation.
	void defineCast(const std::type_info& to, int cast);

	/// Defines a cast mapping from a type to a callback to determine an
	/// operation.
	void defineCast(const std::type_info& to, TypeCallback cb);

	Type();
public:
	/// Returns whether or not this type is signed.
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

	/// Gets a pointer to this type.
	Type* getPointerTo();

	/// Gets the contained type, or this
	virtual Type* getBaseTy();

	/// Gets the root type.
	virtual Type* getRootTy();

	/// Gets the unique signature of this type.
	virtual std::string getSignature() const;

	/// Gets the cast operation to convert to another type.
	int castOperation(Type* to);

	/// Compare the precedence of two types.
	/// @param source The source type to check.
	/// @param target The target type to check against.
	static Comparison compare(Type* source, Type* target);

	/// Gets the internal LLVM type of this type.
	llvm::Type* getLLVMType() const;

	virtual ~Type();
};
