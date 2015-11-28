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

#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>
#include <util/file.h>
#include <util/link.h>
#include <util/string.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/ADT/Triple.h>
#include <llvm/MC/SubtargetFeature.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>


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
		throw fatal_error("could not create engine");
	}

	engine->clearAllGlobalMappings();
	engine->finalizeObject();

	auto func = run_module->getMain()->getLLVMFunction();

	std::vector<llvm::GenericValue> args;
	auto status = engine->runFunction(func, args);
	
	delete engine;

	return status.IntVal.getSExtValue();
}

void Builder::link(std::string outputPath)
{
	auto options = getLinkFlags();

	if (outputPath == "")
	{
#ifdef _WIN32
		outputPath = "a.exe";
#else
		outputPath = "a.out";
#endif
	}

	options.push_back("-o");
	options.push_back(outputPath.c_str());

	std::vector<const char*> tempFiles;

	for (auto mod : m_modules)
	{
		auto path = stringToCharArray(mod->compile());
		options.push_back(path);
		tempFiles.push_back(path);
	}

	invokeLinkerWithOptions(options);

	for (auto temp : tempFiles)
	{
		std::remove(temp);
		delete temp;
	}
}

void Builder::initializeLLVM()
{
	LLVMInitializeNativeTarget();
	LLVMInitializeNativeAsmPrinter();

	std::string err = "";

	auto target_triple = llvm::sys::getProcessTriple();

#ifdef _WIN32
	// Required to run JIT code
	target_triple += "-elf";
#endif 

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

	initializeLLVM();

	auto mod = new Module(this, m_build_path);
	m_modules.push_back(mod);
}

std::vector<const char*> Builder::getLinkFlags() const
{
	std::vector<const char*> options;

	options.push_back(BOOTSTRAP_LOCATION);

#if defined(__APPLE__)
	options.push_back("-w");
	options.push_back("-ldylib1.o");
	options.push_back("-lc");
#elif defined(__linux__)
	options.push_back("-I/lib64/ld-linux-x86-64.so.2");
	options.push_back("-lc");
#elif defined(_WIN32)
	options.push_back("-LC:/Windows/System32");
	options.push_back("-lmsvcrt");
#endif

	return options;
}

Builder::Builder(std::string path)
{
	m_build_path = path;
	m_settings = new BuildSettings();

	initialize();
}

Builder::Builder(std::string path, BuildSettings* settings)
{
	if (settings == nullptr)
	{
		throw fatal_error("settings was null");
	}

	m_build_path = path;
	m_settings = settings;

	initialize();
}

Builder::~Builder()
{
	delete m_library;
	delete m_settings;
	delete m_target_machine;

	for (auto module : m_modules)
	{
		delete module;
	}
}
