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

using namespace llvm::sys;
using namespace llvm;

std::string findProjectDirectory() {
	llvm::SmallString<50> current_path_s; 
	fs::current_path(current_path_s); 
	std::string current_path = Twine(current_path_s).str();
	bool exists = true; 

	// While our current directory exists, try to find ORANGE_SETTINGS
	while (exists) {
		auto path_twine = Twine(current_path);

		std::error_code ec;

		auto end = fs::directory_iterator();
		for (auto it = fs::directory_iterator(path_twine, ec); it != end; it.increment(ec)) {
			if (path::filename(it->path()).str() == ORANGE_SETTINGS) {
				return current_path; 
			}
		}		

		current_path = path::parent_path(current_path);
		exists = fs::exists(Twine(current_path));
	}

	// we didn't find the path, so throw our exception here.
	throw std::runtime_error("fatal: not in an orange project!");
}