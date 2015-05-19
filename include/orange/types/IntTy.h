/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#ifndef __ORANGE_INT_TY_H__
#define __ORANGE_INT_TY_H__

#include "OrangeTy.h"

class IntTy : public OrangeTy {
private:
	bool m_signed = false;
	int m_width = 0;

	IntTy(int width, bool isSigned);

	static std::string getKeyStr(int width, bool isSigned); 
public:
	virtual std::string string() const;
	virtual std::string typeSuffix() const;

	virtual bool isSigned() const { return m_signed; }

	virtual bool isIntegerTy() const { return true; }

	virtual int getIntegerBitWidth() const { return m_width; }

	static IntTy* getSigned(int width);
	static IntTy* getUnsigned(int width);
	static IntTy* get(int width, bool isSigned);
}; 

#endif 