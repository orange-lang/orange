#include <gen/ContinueStatement.h>
#include <gen/ForLoop.h>
#include <gen/generator.h>

std::string ContinueStatement::string() {
	return "CONTINUE";
}

void ContinueStatement::resolve() {
	if (resolved)
		return;
	resolved = true; 

	// nothing to resolve for a continue statement
}

Value* ContinueStatement::Codegen() {
	ForLoop *loop = CG::Symtab()->getLoop();
	if (loop == nullptr) {
		std::cerr << "error: cannot call break while not in a loop.\n";
		exit(1);
	}

	return CG::Builder.CreateBr(loop->getAfterthought());
}



