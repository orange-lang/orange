/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/Builder.h>
#include <grove/BuildSettings.h>
#include <grove/Library.h>
#include <grove/Module.h>
#include <grove/Function.h>
#include <llvm/IR/Module.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>


Library* Builder::getLibrary() const
{
	return m_library;
}

BuildSettings* Builder::getSettings() const
{
	return m_settings;
}

std::vector<Module *> Builder::getModules() const
{
	return m_modules;
}

void Builder::compile()
{
	/// @todo Gather the nodes for library registration.
	/// @todo Build dependency map of those nodes.
	/// @todo Resolve each of those nodes, telling Module which to build
	/// @todo Let those nodes register themselves in the library
	/// @todo Tell each module to import its own registered nodes as headers
	///		  (Look in the library for its LocalNamedTypes and import)
	
	// Resolve the remaining nodes
	for (auto mod : getModules())
	{
		mod->resolve();
	}
	
	for (auto mod : getModules())
	{
		/// @todo Generate code
		mod->build();
	}
}

int Builder::run()
{
	LLVMInitializeNativeTarget();
	LLVMInitializeNativeAsmPrinter();
	
	auto run_module = m_modules[0];
	
	llvm::EngineBuilder builder(
		std::unique_ptr<llvm::Module>(run_module->getLLVMModule()));
	
	std::string error = "";
	
	auto engine = builder
		.setErrorStr(&error)
		.setVerifyModules(true)
		.setEngineKind(llvm::EngineKind::JIT)
		.create();
	
	if (engine == nullptr)
	{
		throw std::runtime_error("could not create engine");
	}
	
	engine->clearAllGlobalMappings();
	engine->finalizeObject();
	
	auto func = run_module->getMain()->getLLVMFunction();
	
	std::vector<llvm::GenericValue> args;
	auto status = engine->runFunction(func, args);
	
	return status.IntVal.getSExtValue();
}

void Builder::initialize()
{
	m_library = new Library();

	if (llvm::sys::fs::is_regular_file(llvm::Twine(m_build_path)) == false)
	{
		throw std::runtime_error("Only regular files are supported currently.");
	}
	
	auto mod = new Module(this, m_build_path);
	m_modules.push_back(mod);
}

Builder::Builder(std::string path)
{
	if (path == "" || llvm::sys::fs::exists(path) == false)
	{
		throw std::invalid_argument("Path must exist.");
	}
	
	m_build_path = path;
	m_settings = new BuildSettings();
	
	initialize();
}

Builder::Builder(std::string path, BuildSettings* settings)
{
	if (path == "" || llvm::sys::fs::exists(path) == false)
	{
		throw std::invalid_argument("Path must exist.");
	}
	
	if (settings == nullptr)
	{
		throw std::invalid_argument("Settings cannot be null.");
	}
	
	m_build_path = path;
	m_settings = settings;
	
	initialize();
}

Builder::~Builder()
{
	delete m_library;
	delete m_settings;
}