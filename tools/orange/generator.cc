#include <orange/generator.h>

GeneratingEngine::GeneratingEngine() {}

GeneratingEngine* GeneratingEngine::sharedEngine() {
	static GeneratingEngine* ge = new GeneratingEngine();
	return ge;
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