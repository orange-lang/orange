/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
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
class ASTNode;

namespace llvm { class Type; }
namespace llvm { class LLVMContext; }
namespace llvm { class Value; }
namespace Orange { class Type; }

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

class Valued;
typedef std::tuple<size_t, size_t> TypeTuple;

typedef std::function<int(const Orange::Type*, const Orange::Type*)>
	TypeCallback;
typedef std::function<llvm::Value*(void*, Valued*, const Orange::Type*,
								   const Orange::Type*)> TypeCast;

const int NO_CAST = 0;

/**
 * Type is the base class for any Orange Type.
 */
class Orange::Type : public ObjectBase {
private:
	/// The map of defined types, where the key is a unique identifier.
	static std::map<std::tuple<Module*,std::string>, Type *> m_defined;
	
	/// The map of type uples to a cast function.
	static std::map<TypeTuple, TypeCast> m_cast_map;
	static std::map<TypeTuple, TypeCallback> m_cast_ty_map;
protected:
	llvm::Type* m_type = nullptr;
	llvm::LLVMContext* m_context = nullptr;
	Module* m_module = nullptr;
	bool m_const = false;

	/// Gets a type given by a signature, if it is defined.
	/// Returns nullptr otherwise.
	static Type* getDefined(Module* mod, std::string signature);

	/// Defines a type with a given signature.
	/// ty must not be null.
	static void define(Module* mod, std::string signature, Type* ty);

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
	/// Deletes all defined types for a specific module.
	static void clear(Module* mod);
	
	/// Gets the string representation of this type.
	virtual std::string getString() const;
	
	/// Returns whether or not this type is signed.
	virtual bool isSigned() const;
	
	/// Gets the module used with this type.
	virtual Module* getModule() const;

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
	virtual bool isNodeTy() const;
	virtual bool isFutureTy() const;
	virtual bool isAggTy() const;
	
	/// Returns true if this type has a reference to an ASTNode.
	virtual bool hasReference() const;
	
	virtual ASTNode* getReference() const;
	
	/// Replaces a member in an aggregate type. Returns the new aggregate.
	virtual const Type* replaceMember(const Type* member, const Type* with)
		const;
	
	/// Gets the member types of an aggregate type.
	virtual std::vector<const Type*> getMemberTys() const;
	
	virtual unsigned int getIntegerBitWidth() const;

	/// Gets plain old data type.
	virtual BasicType PODTy() const;
	
	/// Gets type for comparison. Returns this by default.
	virtual const Type* getComparisonTy() const;

	/// Gets a pointer to this type.
	const Type* getPointerTo() const;

	/// Gets the contained type, or this
	virtual const Type* getBaseTy() const;

	/// Gets the root type.
	virtual const Type* getRootTy() const;
	
	/// Gets a const version of this type.
	virtual const Type* getConst() const;

	/// Gets the unique signature of this type.
	virtual std::string getSignature() const;

	/// Gets whether or not this type is constant.
	bool isConst() const;
	
	virtual bool isVariadiclySized() const;
	
	virtual std::vector<Expression*> getVariadicSizes() const;
	
	/// Gets whether or not this type matches another type.
	/// Returns true if either of the types are VarType.
	virtual bool matches(const Type* ty) const;
	
	/// Compare the precedence of two types.
	/// @param source The source type to check.
	/// @param target The target type to check against.
	static Comparison compare(const Type* source, const Type* target);

	/// Gets the internal LLVM type of this type.
	virtual llvm::Type* getLLVMType() const;
	
	static bool exprValidForArrSize(Expression* expr);
	static unsigned int exprAsArrSize(Expression* expr);
	
	int castOperation(const Type* to) const;
	llvm::Value* cast(void *irBuilder, Valued* val, const Type* target) const;
	
	/// Returns a copy of this type, if this type contains a NodeType.
	/// Otherwise, just returns this.
	virtual const Type* copyType() const;

	virtual ~Type();
};
