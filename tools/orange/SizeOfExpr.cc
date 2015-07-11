/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/SizeOfExpr.h>
#include <orange/generator.h>
#include <sstream>

std::string SizeOfExpr::string() {
	std::stringstream ss; 
	ss << "sizeof("; 

	if (m_type != nullptr) ss << m_type->string(); 
	else if (m_expr != nullptr) ss << m_expr->string(); 

	ss << ")"; 
	return ss.str();
}

unsigned int SizeOfExpr::getPrimitiveSize(OrangeTy* primitive) {
	if (primitive->isIntegerTy()) {
		return primitive->getIntegerBitWidth() / 8; 
	} else if (primitive->isPointerTy()) {
		return 8;
	} else if (primitive->isFloatTy()) {
		return 4; 
	} else if (primitive->isDoubleTy()) {
		return 8;
	} else {
		throw std::runtime_error("type is not a primitive");
	}

	return 0;
}


Value* SizeOfExpr::Codegen() {
	OrangeTy* the_type = m_type;
	if (m_expr != nullptr) the_type = m_expr->getType();
	unsigned int size = 0; 

	std::vector<Value*> multipliers;

	if (the_type->isArrayTy()) {
		// Start with a size of one. 
		size = 1; 

		OrangeTy* typep = the_type;
		while (typep->isArrayTy()) {
			if (typep->isVariadicArray() == false) {
				// Multiply by all of the array sizes in the array.
				size *= typep->getArrayElements();
			} else {
				// Load in the expression. 
				// Multiply it at the end before we return.
				Expression* e = typep->getVariadicArrayElement(); 
				Value* v = e->Codegen();
				if (e->returnsPtr()) v = GE::builder()->CreateLoad(v);
				CastingEngine::CastValueToType(&v, getType(), e->isSigned(), true);
				multipliers.push_back(v);
			}

			typep = typep->getArrayElementType();
		}

		// typep is a primitive now (anything that's not an array)
		size *= getPrimitiveSize(typep);
	} else if (the_type->isIntegerTy() || the_type->isFloatingPointTy() || the_type->isPointerTy()) {
		size = getPrimitiveSize(the_type);
	} else {
		throw std::runtime_error("unexcepeted type");
	}

	Value *curSize = ConstantInt::get(GE::runner()->context(), APInt(64, size)); 

	// Multiply by each of our multipliers now. 
	for (Value* v : multipliers) {
		curSize = GE::builder()->CreateMul(curSize, v);
	}

	m_value = curSize; 
	return m_value;
}

ASTNode* SizeOfExpr::clone() {
	ASTNode* clone = nullptr;

	if (m_expr) {
		clone = new SizeOfExpr(m_expr); 
	} else {
		clone = new SizeOfExpr(m_type);
	}

	clone->copyProperties(this);
	return clone;
}

void SizeOfExpr::resolve() {
	if (m_resolved) return; 
	m_resolved = true;

	if (m_expr) { 
		m_expr->resolve();
	} else if (m_type && m_type->isVariadicArray()) {
		auto tp = m_type; 

		while (tp->isArrayTy()) {
			if (tp->isVariadicArray()) {
				tp->getVariadicArrayElement()->resolve();
			}

			tp = tp->getArrayElementType();
		}
	}
}

SizeOfExpr::SizeOfExpr(OrangeTy* type) {
	m_type = type;

	auto tp = m_type;
	while (tp->isArrayTy()) {
		if (tp->isVariadicArray()) {
			addChild(tp->getVariadicArrayElement());
		}

		tp = tp->getArrayElementType();
	}
}

SizeOfExpr::SizeOfExpr(Expression* expr) {
	m_expr = expr; 
	addChild(expr);
}