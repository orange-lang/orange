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
class Expression;

namespace llvm { class Type; }
namespace llvm { class LLVMContext; }
namespace llvm { class Value; }

/// BasicTypes are plain old data types that are
/// ordered by precedence, descending.
typedef enum {
	TYDOUBLE = 1,
	TYFLOAT,
	TYINT64,
	TYINT32,
	TYINT16,
	TYINT8,
	TYUINT64,
	TYUINT32,
	TYUINT16,
	TYUINT8,
	TYUINT1,
	TYVOID,
	TYOTHER
} BasicType;

class Type;
class Valued;
typedef std::tuple<size_t, size_t> TypeTuple;

typedef std::function<int(Type*,Type*)> TypeCallback;
typedef std::function<llvm::Value*(void*, Valued*, Type*,
								   Type*)> TypeCast;

const int NO_CAST = 0;

/**
 * Type is the base class for any Orange Type.
 */
class Type : public ObjectBase {
private:
	/// The map of defined types, where the key is a unique identifier.
	static std::map<std::string, Type *> m_defined;
	
	/// The map of type uples to a cast function.
	static std::map<TypeTuple, TypeCast> m_cast_map;
	static std::map<TypeTuple, TypeCallback> m_cast_ty_map;
protected:
	llvm::Type* m_type = nullptr;
	llvm::LLVMContext* m_context = nullptr;
	bool m_const = false;

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
	
	/// Defines a cast mapping using a cast function.
	void defineCast(const std::type_info& to, TypeCallback cb, TypeCast func);
	
	/// Defines a cast that uses a cast mapping and a function.
	void defineCast(const std::type_info& to, int cast, TypeCast func);
	
	/// Gets the const identifier for signatures.
	static std::string getConstIdentifier();
	
	void copyCasts(const std::type_info& of);

	Type(bool isConst);
public:
	/// Gets the string representation of this type.
	virtual std::string getString() const;
	
	
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
	virtual bool isBoolTy() const;
	virtual bool isPointerTy() const;
	virtual bool isVoidTy() const;
	virtual bool isVarTy() const;
	virtual bool isClassTy() const;
	
	virtual unsigned int getIntegerBitWidth() const;

	/// Gets plain old data type.
	virtual BasicType PODTy() const;
	
	/// Gets type for comparison. Returns this by default.
	virtual const Type* getComparisonTy() const;

	/// Gets a pointer to this type.
	Type* getPointerTo() const;

	/// Gets the contained type, or this
	virtual Type* getBaseTy() const;

	/// Gets the root type.
	virtual Type* getRootTy() const;
	
	/// Gets a const version of this type.
	virtual Type* getConst() const;

	/// Gets the unique signature of this type.
	virtual std::string getSignature() const;

	/// Gets whether or not this type is constant.
	bool isConst() const;
	
	virtual bool isVariadiclySized() const;
	
	virtual std::vector<Expression*> getVariadicSizes() const;
	
	/// Gets whether or not this type matches another type.
	/// Returns true if either of the types are VarType.
	bool matches(Type* ty) const;
	
	/// Compare the precedence of two types.
	/// @param source The source type to check.
	/// @param target The target type to check against.
	static Comparison compare(const Type* source, const Type* target);

	/// Gets the internal LLVM type of this type.
	llvm::Type* getLLVMType() const;
	
	static bool exprValidForArrSize(Expression* expr);
	static unsigned int exprAsArrSize(Expression* expr);
	
	int castOperation(Type* to);
	llvm::Value* cast(void *irBuilder, Valued* val, Type* target);

	virtual ~Type();
};
