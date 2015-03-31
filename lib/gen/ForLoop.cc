#include <gen/ForLoop.h>
#include <helper/string.h>
#include <gen/generator.h>

std::string ForLoop::string() {
	CG::Symtabs.push(body->symtab);

	std::stringstream ss; 
	ss << "[ ID " << body->symtab->ID << " , PARENT: " << body->symtab->parent->ID << " ] ";
	ss << "for ( "; 
	if (initializer)
		ss << initializer->string(); 
	ss << " ; ";
	if (condition)
		ss << condition->string();
	ss << " ; "; 
	if (afterthought)
		ss << afterthought->string();
	ss << " ):\n";

	std::vector<std::string> lines = split(body->string(), '\n');
	for (std::string line : lines) {
		ss << "\t" << line << std::endl;
	}


	CG::Symtabs.pop();

	return ss.str();
}

void ForLoop::resolve() {
	if (resolved)
		return;
	resolved = true; 

	if (body->symtab == nullptr) {
		std::cerr << "fatal: body of for loop was not assigned a symbol table.\n";
		exit(1);
	}


	CG::Symtabs.push(body->symtab);

	if (initializer) initializer->resolve();
	if (condition) condition->resolve();
	if (afterthought) afterthought->resolve();

	if (condition && condition->getType()->isIntegerTy() == false) {
		std::cerr << "fatal: condition in for loop is not an integer type.\n";
		exit(1);
	}

	body->resolve();

	CG::Symtabs.pop();
}

Value* ForLoop::Codegen() {
	// First, we want to go to the symtab of our body and push it. 
	CG::Symtabs.push(body->symtab);

	// First, we want to do a codegen on the initializer (if it exists)
	if (initializer) {
		initializer->Codegen();
	}

	CG::Symtab()->Loop = this;

	// Now, we want to create three blocks: condition, body, and continue. 
	ConditionBB = BasicBlock::Create(getGlobalContext(), "condition", CG::Symtab()->getFunction(), CG::Symtab()->getFunctionEnd());
	BodyBB = BasicBlock::Create(getGlobalContext(), "body", CG::Symtab()->getFunction(), CG::Symtab()->getFunctionEnd());
	ContinueBB = BasicBlock::Create(getGlobalContext(), "continueLoop", CG::Symtab()->getFunction(), CG::Symtab()->getFunctionEnd());
	AfterthoughtBB = BasicBlock::Create(getGlobalContext(), "afterthought", CG::Symtab()->getFunction(), CG::Symtab()->getFunctionEnd());

	// If we're a post test, we go right to the loop first.
	if (attribs & POST_TEST) {
		CG::Builder.CreateBr(BodyBB);	
	} else {
		CG::Builder.CreateBr(ConditionBB);	
	}

	// The condition block will check to see if the condition code is true. 
	// 		if it is, it jumps to body. 
	//		otherwise, it jumps to continue, the new entry point. 
	CG::Builder.SetInsertPoint(ConditionBB);
	if (condition) {
		auto conditionResult = condition->Codegen(); 
		CG::Builder.CreateCondBr(conditionResult, BodyBB, ContinueBB);				
	} else {
		CG::Builder.CreateBr(BodyBB);
	}

	// The body block will contain all the statements for the body. 
	CG::Builder.SetInsertPoint(BodyBB);
	body->Codegen();

	// At the end of the body block, jump to afterthought, and go 
	// back to the condition.
	if (body->hasJmpInstr() == false) {
		CG::Builder.CreateBr(AfterthoughtBB);
	}

	CG::Builder.SetInsertPoint(AfterthoughtBB);
	if (afterthought)
		afterthought->Codegen();
	CG::Builder.CreateBr(ConditionBB);

	// Set the entry point to the continue block.
	CG::Builder.SetInsertPoint(ContinueBB);

	CG::Symtabs.pop();

	return nullptr; 
}

ForLoop::ForLoop(Statement *initializer, Expression *condition, Expression *afterthought, Block *body, LoopAttributes attribs) { 
	this->initializer = initializer; 
	this->condition = condition; 
	this->afterthought = afterthought; 
	this->attribs = attribs;

	this->body = body; 

	if (this->body == nullptr) {
		std::cerr << "fatal: a for loop requires a body, even if it has no statements.\n";
		exit(1);
	}
}

ForLoop::~ForLoop() {
	if (initializer) delete initializer; 
	if (condition) delete condition; 
	if (afterthought) delete afterthought; 
	delete body; 
}