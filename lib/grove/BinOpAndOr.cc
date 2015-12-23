/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/BinOpAndOr.h>
#include <grove/Module.h>
#include <grove/Function.h>

#include <grove/types/Type.h>
#include <grove/types/BoolType.h>

#include <grove/exceptions/binop_error.h>
#include <grove/exceptions/fatal_error.h>

#include <util/assertions.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constants.h>

ASTNode* BinOpAndOr::copy() const
{
	return new BinOpAndOr(*this);
}

void BinOpAndOr::resolve()
{
	auto lhs_ty = getLHS()->getType();
	auto rhs_ty = getRHS()->getType();

	assertExists(lhs_ty, "LHS has no type");
	assertExists(rhs_ty, "RHS has no type");

	if (lhs_ty->isBoolTy() == false || rhs_ty->isBoolTy() == false)
	{
		auto bool_ty = BoolType::get(getModule());
		throw binop_error(this, lhs_ty, getOperator(), rhs_ty,
						  bool_ty, bool_ty);
	}

	// Just copy type from LHS here since it'll always be bool.
	setType(lhs_ty);
}

void BinOpAndOr::build()
{
	auto parent_func = findParent<Function *>();
	auto llvm_func = parent_func->getLLVMFunction();
	auto bool_ty = getLHS()->getType();
	auto const_true = llvm::ConstantInt::get(bool_ty->getLLVMType(), 1);
	
	auto check_rhs = llvm::BasicBlock::Create(getModule()->getLLVMContext(),
		"check_rhs", llvm_func, parent_func->getExit());
	auto cont = llvm::BasicBlock::Create(getModule()->getLLVMContext(),
		"continue", llvm_func, parent_func->getExit());
	
	// Generate LHS
	getLHS()->build();
	
	auto vLHS = getLHS()->getValue();
	assertExists(vLHS, "LHS didn't generate a value!");
	
	auto ptr = IRBuilder()->CreateAlloca(bool_ty->getLLVMType());
	auto val = IRBuilder()->CreateICmpEQ(vLHS, const_true);
	IRBuilder()->CreateStore(val, ptr);
	
	if (getOperator() == "&&")
	{
		// If LHS was true, we need to check RHS, too.
    	IRBuilder()->CreateCondBr(val, check_rhs, cont);
	}
	else if (getOperator() == "||")
	{
		// If LHS was true, we don't need to check LHS.
    	IRBuilder()->CreateCondBr(val, cont, check_rhs);
	}

	// Generate RHS.
	IRBuilder()->SetInsertPoint(check_rhs);
	
	getRHS()->build();
	
	auto vRHS = getRHS()->getValue();
	assertExists(vRHS, "RHS didn't generate a value!");
	val = IRBuilder()->CreateICmpEQ(vRHS, const_true);
	IRBuilder()->CreateStore(val, ptr);
	IRBuilder()->CreateBr(cont);
	
	// Get value of expression
	IRBuilder()->SetInsertPoint(cont);
	setValue(IRBuilder()->CreateLoad(ptr));
}

BinOpAndOr::BinOpAndOr(Expression* LHS, OString op, Expression* RHS)
: BinOpExpr(LHS, op, RHS)
{
	if (op != "&&" && op != "||")
	{
		throw fatal_error("unknown operator given to BinOpAndOr");
	}
}

BinOpAndOr::BinOpAndOr(const BinOpAndOr& other)
: BinOpExpr((Expression *)other.getLHS()->copy(),
			other.getOperator(),
			(Expression *)other.getRHS()->copy())
{
	other.defineCopy(this);
}