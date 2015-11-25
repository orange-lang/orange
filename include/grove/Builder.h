/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>

class Library;
class BuildSettings;
class Module;

namespace llvm { class TargetMachine; }

/**
 * Builder provides methods for building and running an orange project 
 * or single orange file.
 */
class Builder {
private:
	Library* m_library = nullptr;
	BuildSettings* m_settings = nullptr;
	
	std::string m_build_path;
	
	std::vector<Module *> m_modules;
	
	llvm::TargetMachine* m_target_machine;
	
	void initialize();
	void initializeLLVM();
public:
	/// Returns the library.
	Library* getLibrary() const;
	
	/// Returns the current build settings.
	BuildSettings* getSettings() const;
	
	/// Get modules generated by the builder.
	std::vector<Module *> getModules() const;
	
	/// Gets the machine being targeted.
	llvm::TargetMachine* getTargetMachine() const;
	
	/*
	 * Does the following steps:
	 * 		Gathers the nodes for library registration in each module.
	 * 		Builds a dependency map of those nodes, detecting circ refs.
	 *		Asks module to resolve each node in the map.
	 *			Traverse map locally, module will do resolution and track.
	 * 		Lets those nodes register themselves in the library. 
	 *		Tell each module to import its own registered nodes as headers.
	 *			(Looks in the library for its LocalNamedTypes and imports them)
	 *		Tell each module to resolve the remaining nodes.
	 *		Tell each module to generate code.
	 */
	void compile();
	
	/// Runs the code JIT. Returns the exit status.
	int run();
	
	/// Constructs a builder with the default settings.
	Builder(std::string path);
	
	/// Constructs a builder with custom settings.
	Builder(std::string path, BuildSettings* settings);
	
	~Builder();
};