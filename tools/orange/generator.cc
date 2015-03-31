/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/generator.h>

GeneratingEngine::GeneratingEngine() {}

GeneratingEngine* GeneratingEngine::sharedEngine() {
	static GeneratingEngine* ge = new GeneratingEngine();
	return ge;
}

Runner* GeneratingEngine::runner() {
	return sharedEngine()->active();
}

bool GeneratingEngine::addRunner(Runner *runner) {
	// If a runner by this pathname already exists, return false.
	if (m_runners.find(runner->pathname()) != m_runners.end())
		return false;

	m_runners[runner->pathname()] = runner;
	return true;
}

Runner* GeneratingEngine::active() const {
	return m_active; 
}

void GeneratingEngine::setActive(Runner *runner) {
	m_active = runner; 
}

IRBuilder<>* GeneratingEngine::builder() {
	return runner()->builder();
}

Module* GeneratingEngine::module() {
	return runner()->module();
}

FunctionPassManager* GeneratingEngine::functionOptimizer() {
	return runner()->functionOptimizer();
}