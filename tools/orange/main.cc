/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/
#include <iostream>
#include <cmd/args.h>
#include <util/link.h>

int main(int argc, char** argv) {
	cOptions options("Orange WIP");

	// Parse our options
	options.parse(argc, argv);

	options.currentState()->run();

	return 0;
}
