/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_CASTING_ENGINE_H__
#define __ORANGE_CASTING_ENGINE_H__

#include "OrangeTypes.h"

using namespace llvm;

class ASTNode;

enum PredenceComparison {
	LOWER_PRECEDENCE,
	HIGHER_PRECEDENCE,
	SAME_PRECEDENCE, 
	INCOMPATIBLE
};

class CastingEngine {
public:
	/**
	 * Determines whether or not two nodes can interact together. If the types cannot be 
	 * casted to fit each other, then this will return false. The parameters of this function 
	 * are order-independent. 
	 *
	 * @param a The first node to check for compatibility. 
	 * @param b The second node to check for compatibility.
	 *
	 * @return True if the nodes are compatible, false otherwise.
	 */
	static bool AreNodesCompatible(ASTNode* a, ASTNode* b);
	static bool IsNodeCompatible(ASTNode* a, OrangeTy* ty);
	static bool AreTypesCompatible(OrangeTy* a, OrangeTy* ty);

	/**
	 * Determines whether or not a source node can be casted to a destination node. If the source 
	 * node cannot be casted to fit the destination node, then this will return false. The parameters 
	 * of this function may be order-dependant.
	 *
	 * @param src The source node to check for casting.
	 * @param dest The node to check for casting against.
	 *
	 * @return True if src can be casted to dest, false otherwise.
	 */
	static bool CanNodeBeCasted(ASTNode* src, ASTNode* dest); 
	static bool CanNodeBeCasted(ASTNode* src, OrangeTy* ty);
	static bool CanTypesBeCasted(OrangeTy* ty1, OrangeTy* ty2);

	/**
   * Casts the type of a node to the type of another node. If the types are compatible, then 
   * the cast will be successful regardless of whether or not force is set to true. If the types 
   * are incompatible, this method will only succeeded if force is true. 
	 *
	 * This method may throw an exception if a force cast is not yet implemented
	 *
	 * @param from The node to cast.
	 * @param to The node to cast to.
	 * @param force Indicates whether or not this cast should be forced.
	 *
	 * @return Returns true if the cast was successful, false otherwise.
	 */ 
	static bool CastNode(ASTNode* from, ASTNode* to, bool force = false);
	static bool CastNode(ASTNode* from, OrangeTy* target, bool force = false);
	static bool CastValue(Value** val, OrangeTy* from, OrangeTy* target, bool force = false);
	
	/**
	 * Casts two nodes to match types. The type that will be used is determined by type precedence: 
	 * 	- Floating-point numbers have higher precedences than integers. 
	 * 	- The higher the size of a number, the higher its precedence. e.g., uint64 > uint8 and double > float.
	 *	- Signed values take higher precedence than unsigned values.
	 *
	 * @param n1 The first node to cast to match the other.
	 * @param n2 The second node to cast to match the first.
	 *
	 * @return Returns true if the cast was successful, false otherwise.
	 */ 
 	static bool CastToFit(ASTNode *n1, ASTNode* n2);
 	static bool CastToFit(Value** v1, OrangeTy* ty1, Value** v2, OrangeTy* ty2);

	/**
	 * Compares the precedence between two nodes. 
	 * @param ty1 The first node to compare the precedence of.
	 * @param ty2 The second node to compare the precedence against. 
	 * @return If ty1 has a lower precedence, returns LOWER_PRECEDENCE.
	 * If they're equal, returns SAME_PRECEDENCE. If they're incompatible,
	 * returns INCOMPATIBLE, otherwise returns HIGHER_PRECEDENCE.
	 */
	static PredenceComparison Compare(ASTNode* n1, ASTNode* n2);
	static PredenceComparison Compare(ASTNode* n1, OrangeTy* ty);
	static PredenceComparison Compare(OrangeTy* n1, OrangeTy* ty);

	/**
	 * Gets the higher precedence node between two nodes. 
	 *
	 * @param v1 The first node to check the precedence of.
	 * @param v2 The second node to check the precedence of.
	 *
	 * @return Returns v1 if v1 has a higher precedence than v2. Returns v2 if v2 has a higher precedence than v1. 
	 * Returns nullptr if v1 and v2 are incompatible.
	 *
	 * @see CastValueToType
	 */
	static ASTNode* GetHighestPrecedence(ASTNode* v1, ASTNode* v2); 
	static OrangeTy* GetHighestPrecedence(OrangeTy* v1, OrangeTy* ty);
};

#endif
