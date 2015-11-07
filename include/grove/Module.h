/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#pragma once

class Builder;

/**
 * Module hosts methods for compiling a specific object file. It accepts 
 * a single file.
 */
class Module {
private:
	Builder* m_builder = nullptr;
public:
	/// Returns the builder building this module.
	Builder* getBuilder() const;
	
	/// Constructs a new module with a specified builder.
	Module(Builder* builder);
};
