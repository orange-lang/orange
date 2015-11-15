/*
 ** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#include <test/TestLib.h>
#include <test/Comparisons.h>

#include <llvm/IR/Instruction.h>

#include <grove/types/Type.h>
#include <grove/types/ArrayType.h>
#include <grove/types/BoolType.h>
#include <grove/types/DoubleType.h>
#include <grove/types/FloatType.h>
#include <grove/types/FunctionType.h>
#include <grove/types/IntType.h>
#include <grove/types/LocalNamedType.h>
#include <grove/types/NamedType.h>
#include <grove/types/PointerType.h>
#include <grove/types/UIntType.h>
#include <grove/types/VoidType.h>

#define CAST_TEST(name, from, to, expect) \
ADD_TEST(name, #name);\
int name(){\
auto f = from; auto t = to;\
return cmpEq(f->castOperation(t), expect);}

START_TEST_MODULE();

#define C(castType) llvm::Instruction::CastOps::castType

// Int to Int
CAST_TEST(TestInt8ToInt8,   IntType::get(8),  IntType::get(8),  0);
CAST_TEST(TestInt8ToInt16,  IntType::get(8),  IntType::get(16), C(SExt));
CAST_TEST(TestInt8ToInt32,  IntType::get(8),  IntType::get(32), C(SExt));
CAST_TEST(TestInt8ToInt64,  IntType::get(8),  IntType::get(64), C(SExt));
CAST_TEST(TestInt16ToInt8,  IntType::get(16), IntType::get(8),  C(Trunc));
CAST_TEST(TestInt16ToInt16, IntType::get(16), IntType::get(16), 0);
CAST_TEST(TestInt16ToInt32, IntType::get(16), IntType::get(32), C(SExt));
CAST_TEST(TestInt16ToInt64, IntType::get(16), IntType::get(64), C(SExt));
CAST_TEST(TestInt32ToInt8,  IntType::get(32), IntType::get(8),  C(Trunc));
CAST_TEST(TestInt32ToInt16, IntType::get(32), IntType::get(16), C(Trunc));
CAST_TEST(TestInt32ToInt32, IntType::get(32), IntType::get(32), 0);
CAST_TEST(TestInt32ToInt64, IntType::get(32), IntType::get(64), C(SExt));
CAST_TEST(TestInt64ToInt8,  IntType::get(64), IntType::get(8),  C(Trunc));
CAST_TEST(TestInt64ToInt16, IntType::get(64), IntType::get(16), C(Trunc));
CAST_TEST(TestInt64ToInt32, IntType::get(64), IntType::get(32), C(Trunc));
CAST_TEST(TestInt64ToInt64, IntType::get(64), IntType::get(64), 0);

// UInt to UInt
CAST_TEST(TestUInt8ToUInt8,   UIntType::get(8),  UIntType::get(8),  0);
CAST_TEST(TestUInt8ToUInt16,  UIntType::get(8),  UIntType::get(16), C(ZExt));
CAST_TEST(TestUInt8ToUInt32,  UIntType::get(8),  UIntType::get(32), C(ZExt));
CAST_TEST(TestUInt8ToUInt64,  UIntType::get(8),  UIntType::get(64), C(ZExt));
CAST_TEST(TestUInt16ToUInt8,  UIntType::get(16), UIntType::get(8),  C(Trunc));
CAST_TEST(TestUInt16ToUInt16, UIntType::get(16), UIntType::get(16), 0);
CAST_TEST(TestUInt16ToUInt32, UIntType::get(16), UIntType::get(32), C(ZExt));
CAST_TEST(TestUInt16ToUInt64, UIntType::get(16), UIntType::get(64), C(ZExt));
CAST_TEST(TestUInt32ToUInt8,  UIntType::get(32), UIntType::get(8),  C(Trunc));
CAST_TEST(TestUInt32ToUInt16, UIntType::get(32), UIntType::get(16), C(Trunc));
CAST_TEST(TestUInt32ToUInt32, UIntType::get(32), UIntType::get(32), 0);
CAST_TEST(TestUInt32ToUInt64, UIntType::get(32), UIntType::get(64), C(ZExt));
CAST_TEST(TestUInt64ToUInt8,  UIntType::get(64), UIntType::get(8),  C(Trunc));
CAST_TEST(TestUInt64ToUInt16, UIntType::get(64), UIntType::get(16), C(Trunc));
CAST_TEST(TestUInt64ToUInt32, UIntType::get(64), UIntType::get(32), C(Trunc));
CAST_TEST(TestUInt64ToUInt64, UIntType::get(64), UIntType::get(64), 0);

// Int to UInt. Should SExt to keep negative bit.
CAST_TEST(TestInt8ToUInt8,   IntType::get(8),  UIntType::get(8),  0);
CAST_TEST(TestInt8ToUInt16,  IntType::get(8),  UIntType::get(16), C(SExt));
CAST_TEST(TestInt8ToUInt32,  IntType::get(8),  UIntType::get(32), C(SExt));
CAST_TEST(TestInt8ToUInt64,  IntType::get(8),  UIntType::get(64), C(SExt));
CAST_TEST(TestInt16ToUInt8,  IntType::get(16), UIntType::get(8),  C(Trunc));
CAST_TEST(TestInt16ToUInt16, IntType::get(16), UIntType::get(16), 0);
CAST_TEST(TestInt16ToUInt32, IntType::get(16), UIntType::get(32), C(SExt));
CAST_TEST(TestInt16ToUInt64, IntType::get(16), UIntType::get(64), C(SExt));
CAST_TEST(TestInt32ToUInt8,  IntType::get(32), UIntType::get(8),  C(Trunc));
CAST_TEST(TestInt32ToUInt16, IntType::get(32), UIntType::get(16), C(Trunc));
CAST_TEST(TestInt32ToUInt32, IntType::get(32), UIntType::get(32), 0);
CAST_TEST(TestInt32ToUInt64, IntType::get(32), UIntType::get(64), C(SExt));
CAST_TEST(TestInt64ToUInt8,  IntType::get(64), UIntType::get(8),  C(Trunc));
CAST_TEST(TestInt64ToUInt16, IntType::get(64), UIntType::get(16), C(Trunc));
CAST_TEST(TestInt64ToUInt32, IntType::get(64), UIntType::get(32), C(Trunc));
CAST_TEST(TestInt64ToUInt64, IntType::get(64), UIntType::get(64), 0);

// UInt to Int. Should ZExt.
CAST_TEST(TestUInt8ToInt8,   UIntType::get(8),  IntType::get(8),  0);
CAST_TEST(TestUInt8ToInt16,  UIntType::get(8),  IntType::get(16), C(ZExt));
CAST_TEST(TestUInt8ToInt32,  UIntType::get(8),  IntType::get(32), C(ZExt));
CAST_TEST(TestUInt8ToInt64,  UIntType::get(8),  IntType::get(64), C(ZExt));
CAST_TEST(TestUInt16ToInt8,  UIntType::get(16), IntType::get(8),  C(Trunc));
CAST_TEST(TestUInt16ToInt16, UIntType::get(16), IntType::get(16), 0);
CAST_TEST(TestUInt16ToInt32, UIntType::get(16), IntType::get(32), C(ZExt));
CAST_TEST(TestUInt16ToInt64, UIntType::get(16), IntType::get(64), C(ZExt));
CAST_TEST(TestUInt32ToInt8,  UIntType::get(32), IntType::get(8),  C(Trunc));
CAST_TEST(TestUInt32ToInt16, UIntType::get(32), IntType::get(16), C(Trunc));
CAST_TEST(TestUInt32ToInt32, UIntType::get(32), IntType::get(32), 0);
CAST_TEST(TestUInt32ToInt64, UIntType::get(32), IntType::get(64), C(ZExt));
CAST_TEST(TestUInt64ToInt8,  UIntType::get(64), IntType::get(8),  C(Trunc));
CAST_TEST(TestUInt64ToInt16, UIntType::get(64), IntType::get(16), C(Trunc));
CAST_TEST(TestUInt64ToInt32, UIntType::get(64), IntType::get(32), C(Trunc));
CAST_TEST(TestUInt64ToInt64, UIntType::get(64), IntType::get(64), 0);

// Int to Float.
CAST_TEST(TestInt8ToFloat,  IntType::get(8),  FloatType::get(), C(SIToFP));
CAST_TEST(TestInt16ToFloat, IntType::get(16), FloatType::get(), C(SIToFP));
CAST_TEST(TestInt32ToFloat, IntType::get(32), FloatType::get(), C(SIToFP));
CAST_TEST(TestInt64ToFloat, IntType::get(64), FloatType::get(), C(SIToFP));

// UInt to Float.
CAST_TEST(TestUInt8ToFloat,  UIntType::get(8),  FloatType::get(), C(SIToFP));
CAST_TEST(TestUInt16ToFloat, UIntType::get(16), FloatType::get(), C(SIToFP));
CAST_TEST(TestUInt32ToFloat, UIntType::get(32), FloatType::get(), C(SIToFP));
CAST_TEST(TestUInt64ToFloat, UIntType::get(64), FloatType::get(), C(SIToFP));

// Int to Double.
CAST_TEST(TestInt8ToDouble,  IntType::get(8),  DoubleType::get(), C(SIToFP));
CAST_TEST(TestInt16ToDouble, IntType::get(16), DoubleType::get(), C(SIToFP));
CAST_TEST(TestInt32ToDouble, IntType::get(32), DoubleType::get(), C(SIToFP));
CAST_TEST(TestInt64ToDouble, IntType::get(64), DoubleType::get(), C(SIToFP));

// UInt to Double.
CAST_TEST(TestUInt8ToDouble,  UIntType::get(8),  DoubleType::get(), C(SIToFP));
CAST_TEST(TestUInt16ToDouble, UIntType::get(16), DoubleType::get(), C(SIToFP));
CAST_TEST(TestUInt32ToDouble, UIntType::get(32), DoubleType::get(), C(SIToFP));
CAST_TEST(TestUInt64ToDouble, UIntType::get(64), DoubleType::get(), C(SIToFP));

// Int to Pointer.
CAST_TEST(TestInt8ToPointer,  IntType::get(8),  PointerType::get(BoolType::get()), C(IntToPtr));
CAST_TEST(TestInt16ToPointer, IntType::get(16), PointerType::get(BoolType::get()), C(IntToPtr));
CAST_TEST(TestInt32ToPointer, IntType::get(32), PointerType::get(BoolType::get()), C(IntToPtr));
CAST_TEST(TestInt64ToPointer, IntType::get(64), PointerType::get(BoolType::get()), C(IntToPtr));

// UInt to Pointer.
CAST_TEST(TestUInt8ToPointer,  UIntType::get(8),  PointerType::get(BoolType::get()), C(IntToPtr));
CAST_TEST(TestUInt16ToPointer, UIntType::get(16), PointerType::get(BoolType::get()), C(IntToPtr));
CAST_TEST(TestUInt32ToPointer, UIntType::get(32), PointerType::get(BoolType::get()), C(IntToPtr));
CAST_TEST(TestUInt64ToPointer, UIntType::get(64), PointerType::get(BoolType::get()), C(IntToPtr));

// FP to FP.
CAST_TEST(TestFloatToFloat,   FloatType::get(),  FloatType::get(),  0);
CAST_TEST(TestFloatToDouble,  FloatType::get(),  DoubleType::get(), C(FPExt));

CAST_TEST(TestDoubleToDouble, DoubleType::get(), DoubleType::get(), 0);
CAST_TEST(TestDoubleToFloat,  DoubleType::get(), FloatType::get(),  C(FPTrunc));

// Float to Int
CAST_TEST(TestFloatToInt8,  FloatType::get(), IntType::get(8),  C(FPToSI));
CAST_TEST(TestFloatToInt16, FloatType::get(), IntType::get(16), C(FPToSI));
CAST_TEST(TestFloatToInt32, FloatType::get(), IntType::get(32), C(FPToSI));
CAST_TEST(TestFloatToInt64, FloatType::get(), IntType::get(64), C(FPToSI));

// Float to UInt
CAST_TEST(TestFloatToUInt8,  FloatType::get(), UIntType::get(8),  C(FPToUI));
CAST_TEST(TestFloatToUInt16, FloatType::get(), UIntType::get(16), C(FPToUI));
CAST_TEST(TestFloatToUInt32, FloatType::get(), UIntType::get(32), C(FPToUI));
CAST_TEST(TestFloatToUInt64, FloatType::get(), UIntType::get(64), C(FPToUI));

// Double to Int.
CAST_TEST(TestDoubleToInt8,  DoubleType::get(), IntType::get(8),  C(FPToSI));
CAST_TEST(TestDoubleToInt16, DoubleType::get(), IntType::get(16), C(FPToSI));
CAST_TEST(TestDoubleToInt32, DoubleType::get(), IntType::get(32), C(FPToSI));
CAST_TEST(TestDoubleToInt64, DoubleType::get(), IntType::get(64), C(FPToSI));

// Double to UInt.
CAST_TEST(TestDoubleToUInt8,  DoubleType::get(), UIntType::get(8),  C(FPToUI));
CAST_TEST(TestDoubleToUInt16, DoubleType::get(), UIntType::get(16), C(FPToUI));
CAST_TEST(TestDoubleToUInt32, DoubleType::get(), UIntType::get(32), C(FPToUI));
CAST_TEST(TestDoubleToUInt64, DoubleType::get(), UIntType::get(64), C(FPToUI));

// Pointer to Int.
CAST_TEST(TestPointerToInt8,  PointerType::get(BoolType::get()), IntType::get(8),  C(PtrToInt));
CAST_TEST(TestPointerToInt16, PointerType::get(BoolType::get()), IntType::get(16), C(PtrToInt));
CAST_TEST(TestPointerToInt32, PointerType::get(BoolType::get()), IntType::get(32), C(PtrToInt));
CAST_TEST(TestPointerToInt64, PointerType::get(BoolType::get()), IntType::get(64), C(PtrToInt));

// Pointer to UInt.
CAST_TEST(TestPointerToUInt8,  PointerType::get(BoolType::get()), UIntType::get(8),  C(PtrToInt));
CAST_TEST(TestPointerToUInt16, PointerType::get(BoolType::get()), UIntType::get(16), C(PtrToInt));
CAST_TEST(TestPointerToUInt32, PointerType::get(BoolType::get()), UIntType::get(32), C(PtrToInt));
CAST_TEST(TestPointerToUInt64, PointerType::get(BoolType::get()), UIntType::get(64), C(PtrToInt));

// Pointer to Pointer.
CAST_TEST(TestPointerToPointer, PointerType::get(BoolType::get()), PointerType::get(BoolType::get()), C(BitCast));

RUN_TESTS();