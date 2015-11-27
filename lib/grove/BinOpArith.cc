/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/BinOpArith.h>
#include <grove/types/Type.h>

#include <grove/exceptions/fatal_error.h>
#include <grove/exceptions/binop_error.h>

#include <util/assertions.h>
#include <util/llvmassertions.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstrTypes.h>

#include <map>
#include <tuple>

static llvm::Instruction::BinaryOps getBinOp(std::string op, bool FP, bool isSigned)
{
	typedef llvm::Instruction::BinaryOps BinOp;
	typedef std::tuple<BinOp, BinOp, BinOp> BinOpTuple;
	
	using namespace llvm;
	
	const static std::map<std::string, BinOpTuple> m_op_map = {
		{"+", {BinOp::Add,  BinOp::Add,  BinOp::FAdd}},
		{"-", {BinOp::Sub,  BinOp::Sub,  BinOp::FSub}},
		{"*", {BinOp::Mul,  BinOp::Mul,  BinOp::FMul}},
		{"/", {BinOp::UDiv, BinOp::SDiv, BinOp::FDiv}},
		{"%", {BinOp::URem, BinOp::URem, BinOp::FRem}},
		{"|", {BinOp::Or,   BinOp::Or,   BinOp::BinaryOpsEnd}},
		{"&", {BinOp::And,  BinOp::And,  BinOp::BinaryOpsEnd}},
		{"^", {BinOp::Xor,  BinOp::Xor,  BinOp::BinaryOpsEnd}}
	};
	
	auto it = m_op_map.find(op);
	
	if (it == m_op_map.end())
	{
		throw fatal_error("unkown operator given to BinOpArith");
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

ASTNode* BinOpArith::copy() const
{
	auto copiedLHS = getLHS()->copy()->as<Expression *>();
	auto copiedRHS = getRHS()->copy()->as<Expression *>();
	return new BinOpArith(copiedLHS, getOperator(), copiedRHS);
}

void BinOpArith::resolve()
{
	BinOpExpr::resolve();
	
	switch (compare(getLHS(), getRHS()))
	{
		case LOWER_PRECEDENCE:
			setType(getRHS()->getType());
			break;
		case HIGHER_PRECEDENCE:
			setType(getLHS()->getType());
			break;
		case INCOMPATIBLE:
			throw binop_error(this, getLHS()->getType(), getOperator(),
							  getRHS()->getType());
			break;
		case EQUAL:
			setType(getLHS()->getType());
			break;
	}
	
	auto op = getBinOp(getOperator(), isFloatingPointOperation(),
					   areOperandsSigned());
	
	if (op == llvm::Instruction::BinaryOpsEnd)
	{
		throw fatal_error("Could not determine operation");
	}
}

void BinOpArith::build()
{
	getLHS()->build();
	getRHS()->build();
	
	auto vLHS = getLHS()->getValue();
	auto vRHS = getRHS()->getValue();
	
	assertExists(vLHS, "LHS did not generate a value.");
	assertExists(vRHS, "RHS did not generate a value.");
	
	if (requiresCast())
	{
		auto prec = compare(getLHS(), getRHS());
		
		switch (prec)
		{
			case LOWER_PRECEDENCE:
				vLHS = getLHS()->castTo(getRHS());
				break;
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
	
	auto op = getBinOp(getOperator(), isFloatingPointOperation(),
					   areOperandsSigned());
	
	assertEqual(vLHS, vRHS, "LHS and RHS do not have the same type!");
	
	auto value = IRBuilder()->CreateBinOp(op, vLHS, vRHS);
	setValue(value);
}

BinOpArith::BinOpArith(Expression* LHS, OString op, Expression* RHS)
: BinOpExpr(LHS, op, RHS)
{
	// Do nothing.
}