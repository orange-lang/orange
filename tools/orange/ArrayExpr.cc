/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/ArrayExpr.h>
#include <orange/generator.h>

std::string ArrayExpr::string() {
	std::stringstream ss; 

	ss << "[ "; 

	for (int i = 0; i < m_elements.size(); i++) {
		ss << m_elements[i]->string();

		if (i + 1 < m_elements.size()) {
			ss << ", ";
		}
	}

	ss << " ]";

	return ss.str();
}

Value* ArrayExpr::Codegen() {
	// 1. allocate space for our expr 
	// 2. check if we're a constant array 
	//		a. if we are a constant array:
	//			i. use vector<Constant *> 
	//			ii. push back each code generated expr into the vactor  
	//			iii. create array from ConstantArray::get  
	//			iv. store array into our allocated space 
	//		b. if we're not a constant array: 
	//			i. go through each of our elements 
	//			ii. GEP (getelementpointer) to element i (space, 0, i) in the allocated space 
	//			iii. store our code generated expr into the GEP 
	// 3. return our allocated space 

	AnyType* arrType = getType();
	Value* space = arrType->allocate();

	if (isConstant()) {
		std::vector<Constant *> consts; 

		for (auto element : m_elements) {
			Value* arr_ele = element->Codegen();

			// Cast it to the type of the array 
			CastingEngine::CastValueToType(&arr_ele, arrType->getElementType(), element->isSigned(), true);

			consts.push_back((Constant *)arr_ele);
		}

		Value* storeArr = ConstantArray::get((ArrayType *)arrType->getLLVMType(), consts);
		GE::builder()->CreateStore(storeArr, space);
	} else {
		for (int i = 0; i < m_elements.size(); i++) {
			Value* arr_ele = m_elements[i]->Codegen();

			// This is only necessary for the non-constant array since constant exprs 
			// will never require to be loaded 
			if (m_elements[i]->returnsPtr()) {
				arr_ele = GE::builder()->CreateLoad(arr_ele);
			}

			// Cast it to the type of the array 
			CastingEngine::CastValueToType(&arr_ele, arrType->getElementType(), m_elements[i]->isSigned(), true);

			Value *gep = GE::builder()->CreateConstInBoundsGEP2_64(space, 0, i);
			GE::builder()->CreateStore(arr_ele, gep);		
		}
	}

	return space;
}

ASTNode* ArrayExpr::clone() {
	ArgList cloned_elements; 

	for (auto element : m_elements) {
		cloned_elements.push_back((Expression *)element->clone());
	}

	return new ArrayExpr(cloned_elements);
}

AnyType* ArrayExpr::getType() {
	// If we don't have any elements, we're an int*. 
	if (m_elements.size() == 0) {
		return AnyType::getIntNTy(64)->getPointerTo();
	}

	// We need to get the highest precedence type from all the elements.
	AnyType* highestType = m_elements[0]->getType();

	for (int i = 1; i < m_elements.size(); i++) {
		highestType = CastingEngine::GetFittingType(highestType, m_elements[i]->getType());
	}

	AnyType* ret = highestType->getArray(m_elements.size());
	return ret; 
}

void ArrayExpr::resolve() {
	if (m_resolved) return;
	m_resolved = true ;

	for (auto element : m_elements) {
		element->resolve();
	}
}

bool ArrayExpr::isConstant() {
	for (auto element : m_elements) {
		if (element->isConstant() == false) 
			return false; 
	}

	// Only return true if nothing else returned false.
	return true; 
}


ArrayExpr::ArrayExpr(ArgList elements) {
	m_elements = elements;
}
