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

#include <llvm/IR/Module.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/ADT/Triple.h>
#include <llvm/MC/SubtargetFeature.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>

#include <util/assertions.h>

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

llvm::TargetMachine* Builder::getTargetMachine() const
{
	return m_target_machine;
}

void Builder::compile()
{
	/// @todo Gather the nodes for library registration.
	/// @todo Build dependency map of those nodes.
	/// @todo Resolve each of those nodes, telling Module which to build
	/// @todo Let those nodes register themselves in the library
	/// @todo Tell each module to import its own registered nodes as headers
	///		  (Look in the library for its LocalNamedTypes and import)
	
	// Find dependencies for all modules.
	for (auto mod : getModules())
	{
		mod->findDependencies();
	}
	
	// Resolve the remaining nodes
	for (auto mod : getModules())
	{
		mod->resolve();
	}
	
	for (auto mod : getModules())
	{
		mod->build();
	}
}

int Builder::run()
{
	/// @todo This should change to be the main module of the build.
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

void Builder::initializeLLVM()
{
	LLVMInitializeNativeTarget();
	LLVMInitializeNativeAsmPrinter();
	
	std::string err = "";
	
	auto target_triple = llvm::sys::getProcessTriple();
	llvm::Triple triple = llvm::Triple(target_triple);
	
	auto target = llvm::TargetRegistry::lookupTarget(target_triple, err);
	assertExists(target, "Target not found in registry.");
	
	auto name = llvm::sys::getHostCPUName();
	llvm::SubtargetFeatures features;
	
	features.getDefaultSubtargetFeatures(triple);
	auto featuresStr = features.getString();
	
	llvm::TargetOptions options;
	
	m_target_machine = target->createTargetMachine(triple.getTriple(),
	  name, featuresStr, options, llvm::Reloc::Default,
	  llvm::CodeModel::Default);
}

void Builder::initialize()
{
	m_library = new Library();

	if (llvm::sys::fs::is_regular_file(llvm::Twine(m_build_path)) == false)
	{
		throw std::runtime_error("Only regular files are supported currently.");
	}
	
	initializeLLVM();
	
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