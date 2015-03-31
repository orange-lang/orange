#ifndef __FOR_LOOP_H__ 
#define __FOR_LOOP_H__

#include "AST.h"
#include "Block.h"

enum LoopAttributes {
	NONE = 0x0,
	POST_TEST = 0x1, 
	INFINITE_LOOP = 0x2
};

class ForLoop : public Statement {
private:
	LoopAttributes attribs;

	BasicBlock *ConditionBB, *BodyBB, *AfterthoughtBB, *ContinueBB;
public:
	Statement *initializer;
	Expression *condition, *afterthought; 
	Block *body;

	BasicBlock *getCondition() const { return ConditionBB; }
	BasicBlock *getBody() const { return BodyBB; }
	BasicBlock *getContinue() const { return ContinueBB; }
	BasicBlock *getAfterthought() const { return AfterthoughtBB; }

	Value* Codegen();

	virtual std::string getClass() { return "ForLoop"; }

	virtual std::string string();

	virtual bool isConstant() { return false; }

	void resolve();

	virtual Statement* clone() { 
		ForLoop *ret = new ForLoop(
				(Expression *)initializer->clone(), 
				(Expression *)condition->clone(), 
				(Expression *)afterthought->clone(), 
				body->clone());
		return ret; 
	}

	ForLoop(Statement *initializer, Expression *condition, Expression *afterthought, Block *body, LoopAttributes attribs = NONE);

	~ForLoop();
};


#endif 