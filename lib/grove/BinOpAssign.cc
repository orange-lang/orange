/*
** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/BinOpAssign.h>
#include <grove/Module.h>

#include <grove/exceptions/fatal_error.h>
#include <grove/exceptions/binop_error.h>
#include <grove/exceptions/code_error.h>

#include <grove/types/Type.h>
#include <grove/types/FutureType.h>

#include <util/assertions.h>
#include <util/llvmassertions.h>

#include <llvm/IR/IRBuilder.h>

#include <map>
#include <tuple>

static llvm::Instruction::BinaryOps getBinOp(std::string op, bool FP, bool isSigned)
{
	typedef llvm::Instruction::BinaryOps BinOp;
	typedef std::tuple<BinOp, BinOp, BinOp> BinOpTuple;
	
	using namespace llvm;
	
	const static std::map<std::string, BinOpTuple> m_op_map = {
		{"+", std::make_tuple(BinOp::Add,  BinOp::Add,  BinOp::FAdd)},
		{"-", std::make_tuple(BinOp::Sub,  BinOp::Sub,  BinOp::FSub)},
		{"*", std::make_tuple(BinOp::Mul,  BinOp::Mul,  BinOp::FMul)},
		{"/", std::make_tuple(BinOp::UDiv, BinOp::SDiv, BinOp::FDiv)},
		{"%", std::make_tuple(BinOp::URem, BinOp::SRem, BinOp::FRem)},
		{"|", std::make_tuple(BinOp::Or,   BinOp::Or,   BinOp::BinaryOpsEnd)},
		{"&", std::make_tuple(BinOp::And,  BinOp::And,  BinOp::BinaryOpsEnd)},
		{"^", std::make_tuple(BinOp::Xor,  BinOp::Xor,  BinOp::BinaryOpsEnd)}
	};
	
	auto it = m_op_map.find(op);
	
	if (it == m_op_map.end())
	{
		throw fatal_error("unkown operator given to BinOpAssign");
	}
	
	if (FP == true)
	{
		return std::get<2>(it->second);
	}
	else if (isSigned == true)
	{
		return std::get<1>(it->second);
	}
	else
	{
		return std::get<0>(it->second);
	}
}

bool BinOpAssign::doesArithmetic() const
{
	const std::vector<OString> arith_op_list = {
		"+=", "-=", "*=", "/=", "%=", "&=", "|=", "^="
	};
	
	return std::find(arith_op_list.begin(), arith_op_list.end(),
					 getOperator()) != arith_op_list.end();
}

OString BinOpAssign::getArithOp() const
{
	if (doesArithmetic() == false)
	{
		throw fatal_error("unexpected non-arithmetic operator");
	}
	
	return getOperator().str().substr(0, 1);
}

ASTNode* BinOpAssign::copy() const
{
	return new BinOpAssign(*this);
}

void BinOpAssign::resolve()
{
	if (getLHS()->getType()->isFutureTy())
	{
		if (getRHS()->getType()->isFutureTy())
		{
			throw fatal_error("Both LHS and RHS are future types");
		}
		
		getLHS()->getType()->as<FutureType *>()->replace(getRHS()->getType());
		
		if (getLHS()->getType()->isFutureTy())
		{
			throw fatal_error("LHS is still a future type");
		}
	}
	
	BinOpExpr::resolve();
	
	if (getLHS()->hasPointer() == false)
	{
		throw code_error(getLHS(), []() -> std::string
			{
				return "LHS is not an lvalue and cannot be assigned to";
			});
	}
	
	assertExists(getLHS()->getType(), "LHS doesn't have a type");
	setType(getLHS()->getType());
	
	if (getLHS()->getType()->isConst())
	{
		throw code_error(getLHS(), []() -> std::string
			{
				return "cannot assign a value to a constant variable";
			});
	}
	
	if (doesArithmetic())
	{
		auto op = getBinOp(getArithOp(), isFloatingPointOperation(),
					   areOperandsSigned());
	
    	if (op == llvm::Instruction::BinaryOpsEnd)
    	{
			throw fatal_error("Could not determine operation");
    	}
	}

}

void BinOpAssign::build()
{
	getModule()->build(getLHS());
	getModule()->build(getRHS());
	
	auto vLHS = getLHS()->getValue();
	auto vRHS = getRHS()->getValue();
	
	assertExists(vLHS, "LHS did not generate a value.");
	assertExists(vRHS, "RHS did not generate a value.");
	
	// Cast RHS to LHS if LHS != RHS
	if (requiresCast())
	{
		auto prec = compare(getLHS(), getRHS());
		
		switch (prec)
		{
			case LOWER_PRECEDENCE:
			case HIGHER_PRECEDENCE:
				vRHS = getRHS()->castTo(getLHS());
				break;
			case INCOMPATIBLE:
				throw binop_error(this, getLHS()->getType(), getOperator(),
								  getRHS()->getType());
				break;
			default:
				// Do nothing
				break;
		}
	}
	
	assertEqual(vLHS, vRHS, "LHS and RHS do not have the same type!");
	
	auto val = vRHS;
	
	if (doesArithmetic())
	{
		auto op = getBinOp(getArithOp(), getLHS()->getType()->isFloatingPointTy(),
						   areOperandsSigned());
		val = IRBuilder()->CreateBinOp(op, vLHS, val);
	}
	
	auto ptr = getLHS()->getPointer();
	assertExists(ptr, "LHS didn't give a pointer");
	
	assertEqual<VAL, PTR>(val, ptr, "Can't assign RHS to address");
	IRBuilder()->CreateStore(val, ptr);
	
	setValue(vRHS);
}

BinOpAssign::BinOpAssign(Expression* LHS, OString op, Expression* RHS)
:BinOpExpr(LHS, op, RHS)
{
	if (op != "="  && op != "+=" && op != "-=" && op != "*=" && op != "/=" &&
		op != "%=" && op != "|=" && op != "&=" && op != "^=")
	{
		throw fatal_error("unkown assign operator given to BinOpAssign");
	}
}

BinOpAssign::BinOpAssign(const BinOpAssign& other)
: BinOpExpr((Expression *)other.getLHS()->copy(),
			other.getOperator(),
			(Expression *)other.getRHS()->copy())
{
	other.defineCopy(this);
}