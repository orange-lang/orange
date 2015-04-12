/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/Loop.h>
#include <orange/FunctionStmt.h>
#include <orange/generator.h>

ASTNode* Loop::initilizer() const {
	return m_initializer;
}

Expression* Loop::condition() const {
	return m_condition; 
}

Expression* Loop::afterthought() const {
	return m_afterthought; 
}

BasicBlock* Loop::conditionBlock() const {
	return m_condition_block;
}

BasicBlock* Loop::bodyBlock() const {
	return m_body_block;
}

BasicBlock* Loop::afterthoughtBlock() const {
	return m_afterthought_block;
}

BasicBlock* Loop::continueBlock() const {
	return m_continue_block;
}

bool Loop::isForLoop() const {
	return (m_is_a_while_loop == false);
}

bool Loop::isWhileLoop() const {
	return m_is_a_while_loop && (m_post_check == false);
}

bool Loop::isDoWhileLoop() const {
	return m_is_a_while_loop && (m_post_check == true);
}

bool Loop::isForeverLoop() const {
	return m_initializer == nullptr && m_condition == nullptr && m_afterthought == nullptr;
}

Value* Loop::Codegen() {
	// First, we create our blocks.
	m_condition_block    = getContainingFunction()->createBasicBlock("condition");
	m_body_block         = getContainingFunction()->createBasicBlock("body");
	m_afterthought_block = getContainingFunction()->createBasicBlock("afterthought");
	m_continue_block     = getContainingFunction()->createBasicBlock("continueLoop");

	// Now, we do our logic. 
	pushBlock();

	// First, if we have an initializer, create it.
	if (m_initializer) {
		m_initializer->Codegen();
	}

	// Now, if we're a for loop or a while loop, we jump to the condition block.
	// If we're a do while loop or an infinite loop, we jump to the body block.
	if (isForLoop() || isWhileLoop()) {
		GE::builder()->CreateBr(m_condition_block);
	} else if (isDoWhileLoop() || isForeverLoop()) {
		GE::builder()->CreateBr(m_body_block);
	} else {
		throw std::runtime_error("Unknown loop type!");
	}

	// Regardless of our loop type, we'll generate the condition block first.
	// Generate the condition, and then do a CondBr: if condition is true, go to 
	// the body, otherwise go to continue.
	GE::builder()->SetInsertPoint(m_condition_block);

	if (m_condition) {
		// Generate our condition and then try casting it to a boolean; if it can't,
		// then throw an error. 
		Value* conditionV = m_condition->Codegen();

		if (m_condition->returnsPtr()) {
			conditionV = GE::builder()->CreateLoad(conditionV);
		}


		bool casted = CastingEngine::CastValueToType(&conditionV, AnyType::getUIntNTy(1), m_condition->isSigned(), true);
		if (casted == false) {
			throw CompilerMessage(*m_condition, "cannot cast condition to boolean!");	
		}

		// Now we can generate our condition.
		GE::builder()->CreateCondBr(conditionV, m_body_block, m_continue_block);
	} else {
		// Jump straight to our body.
		GE::builder()->CreateBr(m_body_block);
	}

	// Next, generate the body. 
	GE::builder()->SetInsertPoint(m_body_block);

	generateStatements();

	// After the body is generated, if it doesn't have a return statement, 
	// jump to the afterthought. 
	if (m_body_block->getTerminator() == nullptr) {
		GE::builder()->CreateBr(m_afterthought_block);
	}

	// Generate the afterthought if it exists, then jump back to the condition.
	GE::builder()->SetInsertPoint(m_afterthought_block);

	if (m_afterthought) {
		m_afterthought->Codegen();
	}

	GE::builder()->CreateBr(m_condition_block);

	// We've generated our body; now we can just go to our continue block and leave.
	GE::builder()->SetInsertPoint(m_continue_block);

	popBlock();

	// Loops don't return anything.
	return nullptr; 
}

ASTNode* Loop::clone() {
	if (isForLoop()) {
		Expression* initializer  = m_initializer  ? (Expression*)m_initializer->clone()  : nullptr;
		Expression* condition    = m_condition    ? (Expression*)m_condition->clone()    : nullptr;
		Expression* afterthought = m_afterthought ? (Expression*)m_afterthought->clone() : nullptr;

		return new Loop(initializer, condition, afterthought, symtab()->clone());
	} else if (isWhileLoop() || isDoWhileLoop()) {
		Expression* condition    = m_condition    ? (Expression*)m_condition->clone()    : nullptr;

		return new Loop(condition, m_post_check, symtab()->clone());		
	} else {
		return new Loop(symtab()->clone());
	}
}

void Loop::resolve() {
	if (m_resolved) return;

	// As with all things that inherit from block, we need to push our symtab first.
	GE::runner()->pushBlock(this);

	if (m_initializer) m_initializer->resolve();
	if (m_condition) m_condition->resolve();
	if (m_afterthought) m_afterthought->resolve();

	GE::runner()->popBlock();

	// We'll let our super class handle the rest now.
	Block::resolve();
}

Loop::Loop(ASTNode* initializer, Expression* condition, Expression* afterthought, SymTable* symtab) : Block(symtab) {
	m_initializer = initializer; 
	m_condition = condition; 
	m_afterthought = afterthought; 
}

Loop::Loop(Expression* condition, bool postCheck, SymTable* symtab) : Block(symtab) {
	m_condition = condition; 
	m_post_check = postCheck; 
	m_is_a_while_loop = true;
}

Loop::Loop(SymTable* symtab) : Block(symtab) {
	// Nothing to do here
}
