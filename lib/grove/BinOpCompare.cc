/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <grove/BinOpCompare.h>

#include <grove/types/BoolType.h>

#include <grove/exceptions/fatal_error.h>
#include <grove/exceptions/binop_error.h>

#include <util/assertions.h>
#include <util/llvmassertions.h>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstrTypes.h>

#include <map>
#include <tuple>

static llvm::CmpInst::Predicate getPredicate(std::string op, bool FP, bool isSigned)
{
	typedef llvm::CmpInst::Predicate Pred;
	typedef std::tuple<Pred, Pred, Pred> PredTuple;
	
	using namespace llvm;
	
	const static std::map<std::string, PredTuple> m_op_map = {
		{"<",  std::make_tuple(CmpInst::ICMP_ULT, CmpInst::ICMP_SLT, CmpInst::FCMP_OLT)},
		{">",  std::make_tuple(CmpInst::ICMP_UGT, CmpInst::ICMP_SGT, CmpInst::FCMP_OGT)},
		{"<=", std::make_tuple(CmpInst::ICMP_ULE, CmpInst::ICMP_SLE, CmpInst::FCMP_OLE)},
		{">=", std::make_tuple(CmpInst::ICMP_UGE, CmpInst::ICMP_SGE, CmpInst::FCMP_OGE)},
		{"==", std::make_tuple(CmpInst::ICMP_EQ,  CmpInst::ICMP_EQ,  CmpInst::FCMP_OEQ)},
		{"!=", std::make_tuple(CmpInst::ICMP_NE,  CmpInst::ICMP_NE,  CmpInst::FCMP_ONE)}
	};
	
	auto it = m_op_map.find(op);
	
	if (it == m_op_map.end())
	{
		throw fatal_error("Unkown operator given to BinOpCompare");
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

ASTNode* BinOpCompare::copy() const
{
	auto copiedLHS = getLHS()->copy()->as<Expression *>();
	auto copiedRHS = getRHS()->copy()->as<Expression *>();
	
	return new BinOpCompare(copiedLHS, getOperator(), copiedRHS);
}

void BinOpCompare::resolve()
{
	BinOpExpr::resolve();
	setType(BoolType::get());
}

void BinOpCompare::build()
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
	
	assertEqual(vLHS, vRHS, "LHS and RHS do not have the same type!");
	
	auto predicate = getPredicate(getOperator(), isFloatingPointOperation(),
								  areOperandsSigned());
	llvm::Value* value = nullptr;
	
	if (isFloatingPointOperation())
	{
		value = IRBuilder()->CreateFCmp(predicate, vLHS, vRHS);
	}
	else
	{
		value = IRBuilder()->CreateICmp(predicate, vLHS, vRHS);
	}
	
	setValue(value);
}

BinOpCompare::BinOpCompare(Expression* LHS, OString op, Expression* RHS)
:BinOpExpr(LHS, op, RHS)
{
	// Do nothing.
}