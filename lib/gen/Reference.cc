#include "gen/Reference.h"
#include "gen/generator.h"

std::string Reference::string() {
	std::stringstream ss;
	ss << "&" << value->string();
	return ss.str();
}

Type* Reference::getType() {
	return value->getType()->getPointerTo();
}

void Reference::resolve() {
	if (resolved)
		return;
	resolved = true; 

	value->resolve();
}

Value* Reference::Codegen() {
	Value *v = value->Codegen();
	return v;
}
