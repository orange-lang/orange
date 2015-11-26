/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/BinOpAssign.h>
#include <grove/types/Type.h>
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
		{"+", {BinOp::Add,  BinOp::Add,  BinOp::FAdd}},
		{"-", {BinOp::Sub,  BinOp::Sub,  BinOp::FSub}},
		{"*", {BinOp::Mul,  BinOp::Mul,  BinOp::FMul}},
		{"/", {BinOp::UDiv, BinOp::SDiv, BinOp::FDiv}},
		{"%", {BinOp::URem, BinOp::SRem, BinOp::FRem}},
		{"|", {BinOp::Or,   BinOp::Or,   BinOp::BinaryOpsEnd}},
		{"&", {BinOp::And,  BinOp::And,  BinOp::BinaryOpsEnd}},
		{"^", {BinOp::Xor,  BinOp::Xor,  BinOp::BinaryOpsEnd}}
	};
	
	auto it = m_op_map.find(op);
	
	if (it == m_op_map.end())
	{
		throw std::invalid_argument("op " + op + " not supported.");
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
		throw std::runtime_error("operator does no arithmetic");
	}
	
	return getOperator().str().substr(0, 1);
}

ASTNode* BinOpAssign::copy() const
{
	auto copiedLHS = getLHS()->copy()->as<Expression *>();
	auto copiedRHS = getRHS()->copy()->as<Expression *>();
	
	return new BinOpAssign(copiedLHS, getOperator(), copiedRHS);
}

void BinOpAssign::resolve()
{
	BinOpExpr::resolve();
	
	if (getLHS()->hasPointer() == false)
	{
		throw std::invalid_argument("LHS doesn't refer to a memory address");
	}
	
	assertExists(getLHS()->getType(), "LHS doesn't have a type");
	setType(getLHS()->getType());
	
	if (getLHS()->getType()->isConst())
	{
		throw std::invalid_argument("Cann't assign to a const var");
	}
	
	if (doesArithmetic())
	{
		auto op = getBinOp(getArithOp(), isFloatingPointOperation(),
					   areOperandsSigned());
	
    	if (op == llvm::Instruction::BinaryOpsEnd)
    	{
    		throw std::runtime_error("Cannot do operation");
    	}	
	}

}

void BinOpAssign::build()
{
	getLHS()->build();
	getRHS()->build();
	
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
				throw std::runtime_error("Cannot cast types.");
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
		throw std::invalid_argument("Unknown assign operator");
	}
}