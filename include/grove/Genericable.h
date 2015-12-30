/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#pragma once

#include "Typed.h"

class Type;

/**
 * Genericable represents a class that _can_ be a generic
 * (e.g., one of its members is a VarType). If it is a generic, 
 * methods to create and find unique non-generic instances are 
 * exposed. 
 */
class Genericable : virtual public Typed
{
protected:
	std::vector<Genericable *> m_instances;
public:
	/// Determines whether or not this object is
	/// actually a generic or not.
	virtual bool isGeneric() const = 0;
	
	/// Creates a non-generic instance of this Genericable.
	/// Throws an error if isGeneric() returns false.
	/// @param type The type of the instance.
	/// @return The instance created.
	virtual Genericable* createInstance(const Type* type) = 0;
	
	/// Returns an instance with a given list of types.
	/// Returns nullptr if an instance does not exist,
	/// Throws an error if isGeneric() returns false.
	/// @param type The type the instance should have.
	Genericable* findInstance(const Type* type) const;
	
	/// Returns true if an instance with a given list of types
	/// exists. Throws an error if isGeneric() returns false.
	/// @param type The type the instance should have.
	/// @return True if an instance exists, false otherwise.
	bool hasInstance(const Type* type) const;
};