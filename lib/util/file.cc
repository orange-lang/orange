/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <orange/file.h>
#include <orange/config.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>

//using namespace llvm::sys;
//using namespace llvm;


std::string findProjectDirectory(std::string target)
{
	llvm::SmallString<50> current_path_s;
	llvm::sys::fs::current_path(current_path_s);
	std::string current_path = llvm::Twine(current_path_s).str();
	bool exists = true;

	// While our current directory exists, try to find ORANGE_SETTINGS
	while (exists)
	{
		auto path_twine = llvm::Twine(current_path);

		std::error_code ec;
		
		typedef llvm::sys::fs::directory_iterator llvm_dir_it;

		auto end = llvm_dir_it();
		for (auto it = llvm_dir_it(path_twine, ec); it != end; it.increment(ec))
		{
			if (llvm::sys::path::filename(it->path()).str() == target)
			{
				return current_path;
			}
		}

		// Go to the parent path, making sure it exists.
		current_path = llvm::sys::path::parent_path(current_path);
		exists = llvm::sys::fs::exists(llvm::Twine(current_path));
	}

	// we didn't find the path, so throw our exception here.
	throw std::runtime_error("fatal: not in an orange project!");
}

std::string getWorkingDirectory()
{
	llvm::SmallString<50> buf;
	llvm::sys::fs::current_path(buf);
	return llvm::Twine(buf).str();
}

std::string combinePaths(std::string a, std::string b)
{
	llvm::SmallString<50> buf;
	llvm::sys::path::append(buf, llvm::Twine(a), llvm::Twine(b));
	return llvm::Twine(buf).str();
}

std::string getTempFile(std::string prefix, std::string suffix)
{
	llvm::SmallString<50> buf;
	llvm::sys::fs::createTemporaryFile(llvm::Twine(prefix), suffix, buf);
	return llvm::Twine(buf).str();
}

std::vector<std::string> getFilesRecursive(std::string path)
{
	std::vector<std::string> ret;
	
	std::error_code ec;
	typedef llvm::sys::fs::recursive_directory_iterator llvm_rdir_it;
	auto it = llvm::sys::fs::recursive_directory_iterator(llvm::Twine(path),
														  ec);
	
	if (ec.value() != 0)
	{
		throw std::runtime_error(ec.message());
	}
	
	for ( ; it != llvm_rdir_it(); it.increment(ec))
	{
		auto entry = *it;
	
		auto status = llvm::sys::fs::file_status();
		entry.status(status);
		
		if (status.type() != llvm::sys::fs::file_type::regular_file)
		{
			continue;
		}
		
		// If it's a dotfile, continue on
		auto fname = llvm::sys::path::filename(entry.path());
		if (fname[0] == '.')
		{
			continue;
		}
		ret.push_back(entry.path());
	}
	
	return ret;
}