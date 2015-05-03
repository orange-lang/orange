/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __LOOP_H__
#define __LOOP_H__

#include "AST.h"
#include "Block.h"

class Loop : public Block {
private:
	/** 
	 * There are three parts in a for loop: initilizer, condition, and afterthought:
	 *
	 * 		for (intializer; condition; afterthought)
	 */
	ASTNode*    m_initializer = nullptr;
	Expression* m_condition = nullptr; 
	Expression* m_afterthought = nullptr; 

	/** 
	 *
	 * We have a BasicBlock for our condition and afterthought, alongside a body 
	 * and a continue. The body is where the body of our Loop will go, 
	 * while the continue is where code is generated following this Loop.
	 *
	 */ 

	/** 
	 * The condition block checks to see if the m_condition is true. If it's false, 
	 * then we'll go straight into the continue block. If it's true, will go to the body.
	 * The condition block is the first thing jump to if m_post_check is false.
	 */
	BasicBlock* m_condition_block = nullptr;

	/** 
	 * The body block contains all of our code.
	 * The body block is the first thing jumped to if m_post_check is true.
	 */
	BasicBlock* m_body_block = nullptr;

	/** 
	 * The afterthought block is ran following the body, if an afterthought expression exists.
	 */
	BasicBlock* m_afterthought_block;

	/** 
	 * The continue block is the last thing generated, and we don't put any code inside of it.
	 */
	BasicBlock* m_continue_block;

	/**
	 * If m_post_check is true, then it's a do...while loop.
	 */ 
	bool m_post_check = false; 

	/** 
	 * Determines if this is a while loop.
	 */
	bool m_is_a_while_loop = false;
public:
	virtual std::string getClass() { return "Loop"; }

	virtual std::string string();

	/** 
	 * The initializer is an expression that is ran once before we run any code in the loop. It is only used 
	 * in for loops. After the initializer is ran, we check the condition and then go either straight to the 
	 * body or exit the loop.
	 *
	 * @return The initializer expression for our loop. Will always be nullptr for a while/do...while/forever loop.
	 */
	ASTNode* initilizer() const; 

	/**
	 * The condition is an exprssion that is ran at some point during every loop cycle. If we are a for loop,
	 * the condition is checked before going into the body. If we are a while loop, the condition is checked 
	 * after executing the body. 
	 * 
	 * @return The condition expression for our loop. Will always be nullptr in a forever loop.
	 */
	Expression* condition() const; 

	/**
	 * The afterthought is an expression that is ran once following every loop cycle. It is only used in 
	 * for loops. After the body of a loop is ran, we go straight to our afterthought, run it, and then go 
	 * back to the condition. 
	 * 
	 * @return The afterthought expression for our loop. Will always be nullptr for a while/do...while/forever loop.
	 */
	Expression* afterthought() const;

	/**
	 * @return The block where the condition expression is generated in.
	 */
	BasicBlock* conditionBlock() const; 

	/** 
	 * @return The block where our body of the for loop is generated in.
	 */
	BasicBlock* bodyBlock() const; 

	/**
	 * @return The block where the afterthought expression is generated in.
	 */
	BasicBlock* afterthoughtBlock() const;

	/**
	 * @return The block where the insert point is set to following generation of the complete for loop.
	 */
	BasicBlock* continueBlock() const; 
	
	/** 
	 * @return True if the Loop is a for loop, false otherwise.
	 */
	bool isForLoop() const; 

	/**
	 * @return True if the Loop is a while loop, false otherwise.
	 */
	bool isWhileLoop() const; 

	/**
	 * @return True if the Loop is a do...while loop, false otherwise.
	 */
	bool isDoWhileLoop() const; 

	/**
	 * @return True if the Loop is a forever (read: infinite) loop, false otherwise.
	 */
	bool isForeverLoop() const; 

	/** 
	 * Loops aren't "traditional" blocks.
	 */
	virtual bool isBlock() { return false; }

	virtual void setInitializer(ASTNode* initializer) { m_initializer = initializer; }

	virtual void setCondition(Expression* condition) { m_condition = condition; }
	
	virtual void setAfterthought(Expression* afterthought) { m_afterthought = afterthought; } 

	virtual Value* Codegen();

	virtual ASTNode* clone();

	virtual void resolve();

	/**
	 * Creates a for loop. A for loop takes in a 3 expressions, which can all be null. 
	 * 
	 * @param initializer The initializer expression to be ran before any other part of the loop.
	 * @param condition The condition to be checked before running the body.
	 * @param afterthought The expression to be ran after running the body. 
	 * @param symtab The symbol table for this loop.
	 */
	Loop(ASTNode* initializer, Expression* condition, Expression* afterthought, SymTable* symtab);

	/** 
	 * Creates either a while loop or a do while loop. Either of these only take in a condition,
	 * which is checked before executing the body in a while loop and after in a do while loop.
	 *
	 * @param condition The condition to check.
	 * @param postCheck Determines whether or not this is a do while loop; true if do while, false if while.
	 * @param symtab The symbol table for this loop.
	 */
	Loop(Expression* condition, bool postCheck, SymTable* symtab);

	/**
	 * Creates an infinite loop.
	 * 
	 * @param symtab The symbol table for this loop.
	 */
	Loop(SymTable* symtab);
};

#endif 