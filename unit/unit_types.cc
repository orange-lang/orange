/*
 ** Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
 ** directory of this distribution.
 **
 ** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
 ** may not be copied, modified, or distributed except according to those terms.
 */

#include <test/TestLib.h>
#include <test/Comparisons.h>

#include <llvm/IR/Instruction.h>

#include <libast/types/Type.h>
#include <libast/types/ArrayType.h>
#include <libast/types/BoolType.h>
#include <libast/types/DoubleType.h>
#include <libast/types/FloatType.h>
#include <libast/types/EnumType.h>
#include <libast/types/FunctionType.h>
#include <libast/types/IntType.h>
#include <libast/types/LocalNamedType.h>
#include <libast/types/NamedType.h>
#include <libast/types/PointerType.h>
#include <libast/types/UIntType.h>
#include <libast/types/VoidType.h>

#include <libast/Comparison.h>
#include <libast/Module.h>
#include <libast/Builder.h>



#define CAST_TEST(name, from, to, expect) \
ADD_TEST(name, #name);\
int name(){\
Module mod;\
auto f = from; auto t = to;\
return cmpEq(f->castOperation(t), expect);}

#define PREC_TEST(name, source, target, expect) \
ADD_TEST(name, #name);\
int name(){ \
Module mod;\
return cmpEq(Orange::Type::compare(source, target), expect); }

START_TEST_MODULE();

#define C(castType) llvm::Instruction::CastOps::castType

//////
// Cast tests
//////

// Int to Int
CAST_TEST(TestInt8ToInt8,   Orange::IntType::get(&mod, 8),  Orange::IntType::get(&mod, 8),  NO_CAST);
CAST_TEST(TestInt8ToInt16,  Orange::IntType::get(&mod, 8),  Orange::IntType::get(&mod, 16), C(SExt));
CAST_TEST(TestInt8ToInt32,  Orange::IntType::get(&mod, 8),  Orange::IntType::get(&mod, 32), C(SExt));
CAST_TEST(TestInt8ToInt64,  Orange::IntType::get(&mod, 8),  Orange::IntType::get(&mod, 64), C(SExt));
CAST_TEST(TestInt16ToInt8,  Orange::IntType::get(&mod, 16), Orange::IntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestInt16ToInt16, Orange::IntType::get(&mod, 16), Orange::IntType::get(&mod, 16), NO_CAST);
CAST_TEST(TestInt16ToInt32, Orange::IntType::get(&mod, 16), Orange::IntType::get(&mod, 32), C(SExt));
CAST_TEST(TestInt16ToInt64, Orange::IntType::get(&mod, 16), Orange::IntType::get(&mod, 64), C(SExt));
CAST_TEST(TestInt32ToInt8,  Orange::IntType::get(&mod, 32), Orange::IntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestInt32ToInt16, Orange::IntType::get(&mod, 32), Orange::IntType::get(&mod, 16), C(Trunc));
CAST_TEST(TestInt32ToInt32, Orange::IntType::get(&mod, 32), Orange::IntType::get(&mod, 32), NO_CAST);
CAST_TEST(TestInt32ToInt64, Orange::IntType::get(&mod, 32), Orange::IntType::get(&mod, 64), C(SExt));
CAST_TEST(TestInt64ToInt8,  Orange::IntType::get(&mod, 64), Orange::IntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestInt64ToInt16, Orange::IntType::get(&mod, 64), Orange::IntType::get(&mod, 16), C(Trunc));
CAST_TEST(TestInt64ToInt32, Orange::IntType::get(&mod, 64), Orange::IntType::get(&mod, 32), C(Trunc));
CAST_TEST(TestInt64ToInt64, Orange::IntType::get(&mod, 64), Orange::IntType::get(&mod, 64), NO_CAST);

// UInt to UInt
CAST_TEST(TestUInt8ToUInt8,   Orange::UIntType::get(&mod, 8),  Orange::UIntType::get(&mod, 8),  NO_CAST);
CAST_TEST(TestUInt8ToUInt16,  Orange::UIntType::get(&mod, 8),  Orange::UIntType::get(&mod, 16), C(ZExt));
CAST_TEST(TestUInt8ToUInt32,  Orange::UIntType::get(&mod, 8),  Orange::UIntType::get(&mod, 32), C(ZExt));
CAST_TEST(TestUInt8ToUInt64,  Orange::UIntType::get(&mod, 8),  Orange::UIntType::get(&mod, 64), C(ZExt));
CAST_TEST(TestUInt16ToUInt8,  Orange::UIntType::get(&mod, 16), Orange::UIntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestUInt16ToUInt16, Orange::UIntType::get(&mod, 16), Orange::UIntType::get(&mod, 16), NO_CAST);
CAST_TEST(TestUInt16ToUInt32, Orange::UIntType::get(&mod, 16), Orange::UIntType::get(&mod, 32), C(ZExt));
CAST_TEST(TestUInt16ToUInt64, Orange::UIntType::get(&mod, 16), Orange::UIntType::get(&mod, 64), C(ZExt));
CAST_TEST(TestUInt32ToUInt8,  Orange::UIntType::get(&mod, 32), Orange::UIntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestUInt32ToUInt16, Orange::UIntType::get(&mod, 32), Orange::UIntType::get(&mod, 16), C(Trunc));
CAST_TEST(TestUInt32ToUInt32, Orange::UIntType::get(&mod, 32), Orange::UIntType::get(&mod, 32), NO_CAST);
CAST_TEST(TestUInt32ToUInt64, Orange::UIntType::get(&mod, 32), Orange::UIntType::get(&mod, 64), C(ZExt));
CAST_TEST(TestUInt64ToUInt8,  Orange::UIntType::get(&mod, 64), Orange::UIntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestUInt64ToUInt16, Orange::UIntType::get(&mod, 64), Orange::UIntType::get(&mod, 16), C(Trunc));
CAST_TEST(TestUInt64ToUInt32, Orange::UIntType::get(&mod, 64), Orange::UIntType::get(&mod, 32), C(Trunc));
CAST_TEST(TestUInt64ToUInt64, Orange::UIntType::get(&mod, 64), Orange::UIntType::get(&mod, 64), NO_CAST);

// Int to UInt. Should SExt to keep negative bit.
CAST_TEST(TestInt8ToUInt8,   Orange::IntType::get(&mod, 8),  Orange::UIntType::get(&mod, 8),  NO_CAST);
CAST_TEST(TestInt8ToUInt16,  Orange::IntType::get(&mod, 8),  Orange::UIntType::get(&mod, 16), C(SExt));
CAST_TEST(TestInt8ToUInt32,  Orange::IntType::get(&mod, 8),  Orange::UIntType::get(&mod, 32), C(SExt));
CAST_TEST(TestInt8ToUInt64,  Orange::IntType::get(&mod, 8),  Orange::UIntType::get(&mod, 64), C(SExt));
CAST_TEST(TestInt16ToUInt8,  Orange::IntType::get(&mod, 16), Orange::UIntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestInt16ToUInt16, Orange::IntType::get(&mod, 16), Orange::UIntType::get(&mod, 16), NO_CAST);
CAST_TEST(TestInt16ToUInt32, Orange::IntType::get(&mod, 16), Orange::UIntType::get(&mod, 32), C(SExt));
CAST_TEST(TestInt16ToUInt64, Orange::IntType::get(&mod, 16), Orange::UIntType::get(&mod, 64), C(SExt));
CAST_TEST(TestInt32ToUInt8,  Orange::IntType::get(&mod, 32), Orange::UIntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestInt32ToUInt16, Orange::IntType::get(&mod, 32), Orange::UIntType::get(&mod, 16), C(Trunc));
CAST_TEST(TestInt32ToUInt32, Orange::IntType::get(&mod, 32), Orange::UIntType::get(&mod, 32), NO_CAST);
CAST_TEST(TestInt32ToUInt64, Orange::IntType::get(&mod, 32), Orange::UIntType::get(&mod, 64), C(SExt));
CAST_TEST(TestInt64ToUInt8,  Orange::IntType::get(&mod, 64), Orange::UIntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestInt64ToUInt16, Orange::IntType::get(&mod, 64), Orange::UIntType::get(&mod, 16), C(Trunc));
CAST_TEST(TestInt64ToUInt32, Orange::IntType::get(&mod, 64), Orange::UIntType::get(&mod, 32), C(Trunc));
CAST_TEST(TestInt64ToUInt64, Orange::IntType::get(&mod, 64), Orange::UIntType::get(&mod, 64), NO_CAST);

// UInt to Int. Should ZExt.
CAST_TEST(TestUInt8ToInt8,   Orange::UIntType::get(&mod, 8),  Orange::IntType::get(&mod, 8),  NO_CAST);
CAST_TEST(TestUInt8ToInt16,  Orange::UIntType::get(&mod, 8),  Orange::IntType::get(&mod, 16), C(ZExt));
CAST_TEST(TestUInt8ToInt32,  Orange::UIntType::get(&mod, 8),  Orange::IntType::get(&mod, 32), C(ZExt));
CAST_TEST(TestUInt8ToInt64,  Orange::UIntType::get(&mod, 8),  Orange::IntType::get(&mod, 64), C(ZExt));
CAST_TEST(TestUInt16ToInt8,  Orange::UIntType::get(&mod, 16), Orange::IntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestUInt16ToInt16, Orange::UIntType::get(&mod, 16), Orange::IntType::get(&mod, 16), NO_CAST);
CAST_TEST(TestUInt16ToInt32, Orange::UIntType::get(&mod, 16), Orange::IntType::get(&mod, 32), C(ZExt));
CAST_TEST(TestUInt16ToInt64, Orange::UIntType::get(&mod, 16), Orange::IntType::get(&mod, 64), C(ZExt));
CAST_TEST(TestUInt32ToInt8,  Orange::UIntType::get(&mod, 32), Orange::IntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestUInt32ToInt16, Orange::UIntType::get(&mod, 32), Orange::IntType::get(&mod, 16), C(Trunc));
CAST_TEST(TestUInt32ToInt32, Orange::UIntType::get(&mod, 32), Orange::IntType::get(&mod, 32), NO_CAST);
CAST_TEST(TestUInt32ToInt64, Orange::UIntType::get(&mod, 32), Orange::IntType::get(&mod, 64), C(ZExt));
CAST_TEST(TestUInt64ToInt8,  Orange::UIntType::get(&mod, 64), Orange::IntType::get(&mod, 8),  C(Trunc));
CAST_TEST(TestUInt64ToInt16, Orange::UIntType::get(&mod, 64), Orange::IntType::get(&mod, 16), C(Trunc));
CAST_TEST(TestUInt64ToInt32, Orange::UIntType::get(&mod, 64), Orange::IntType::get(&mod, 32), C(Trunc));
CAST_TEST(TestUInt64ToInt64, Orange::UIntType::get(&mod, 64), Orange::IntType::get(&mod, 64), NO_CAST);

// Int to Float.
CAST_TEST(TestInt8ToFloat,  Orange::IntType::get(&mod, 8),  Orange::FloatType::get(&mod), C(SIToFP));
CAST_TEST(TestInt16ToFloat, Orange::IntType::get(&mod, 16), Orange::FloatType::get(&mod), C(SIToFP));
CAST_TEST(TestInt32ToFloat, Orange::IntType::get(&mod, 32), Orange::FloatType::get(&mod), C(SIToFP));
CAST_TEST(TestInt64ToFloat, Orange::IntType::get(&mod, 64), Orange::FloatType::get(&mod), C(SIToFP));

// UInt to Float.
CAST_TEST(TestUInt8ToFloat,  Orange::UIntType::get(&mod, 8),  Orange::FloatType::get(&mod), C(UIToFP));
CAST_TEST(TestUInt16ToFloat, Orange::UIntType::get(&mod, 16), Orange::FloatType::get(&mod), C(UIToFP));
CAST_TEST(TestUInt32ToFloat, Orange::UIntType::get(&mod, 32), Orange::FloatType::get(&mod), C(UIToFP));
CAST_TEST(TestUInt64ToFloat, Orange::UIntType::get(&mod, 64), Orange::FloatType::get(&mod), C(UIToFP));

// Int to Double.
CAST_TEST(TestInt8ToDouble,  Orange::IntType::get(&mod, 8),  Orange::DoubleType::get(&mod), C(SIToFP));
CAST_TEST(TestInt16ToDouble, Orange::IntType::get(&mod, 16), Orange::DoubleType::get(&mod), C(SIToFP));
CAST_TEST(TestInt32ToDouble, Orange::IntType::get(&mod, 32), Orange::DoubleType::get(&mod), C(SIToFP));
CAST_TEST(TestInt64ToDouble, Orange::IntType::get(&mod, 64), Orange::DoubleType::get(&mod), C(SIToFP));

// UInt to Double.
CAST_TEST(TestUInt8ToDouble,  Orange::UIntType::get(&mod, 8),  Orange::DoubleType::get(&mod), C(UIToFP));
CAST_TEST(TestUInt16ToDouble, Orange::UIntType::get(&mod, 16), Orange::DoubleType::get(&mod), C(UIToFP));
CAST_TEST(TestUInt32ToDouble, Orange::UIntType::get(&mod, 32), Orange::DoubleType::get(&mod), C(UIToFP));
CAST_TEST(TestUInt64ToDouble, Orange::UIntType::get(&mod, 64), Orange::DoubleType::get(&mod), C(UIToFP));

// Int to Pointer.
CAST_TEST(TestInt8ToPointer,  Orange::IntType::get(&mod, 8),  Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), C(IntToPtr));
CAST_TEST(TestInt16ToPointer, Orange::IntType::get(&mod, 16), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), C(IntToPtr));
CAST_TEST(TestInt32ToPointer, Orange::IntType::get(&mod, 32), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), C(IntToPtr));
CAST_TEST(TestInt64ToPointer, Orange::IntType::get(&mod, 64), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), C(IntToPtr));

// UInt to Pointer.
CAST_TEST(TestUInt8ToPointer,  Orange::UIntType::get(&mod, 8),  Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), C(IntToPtr));
CAST_TEST(TestUInt16ToPointer, Orange::UIntType::get(&mod, 16), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), C(IntToPtr));
CAST_TEST(TestUInt32ToPointer, Orange::UIntType::get(&mod, 32), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), C(IntToPtr));
CAST_TEST(TestUInt64ToPointer, Orange::UIntType::get(&mod, 64), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), C(IntToPtr));

// Int to Bool
CAST_TEST(TestInt8ToBool,  Orange::IntType::get(&mod, 8),  Orange::BoolType::get(&mod), C(Trunc));
CAST_TEST(TestInt16ToBool, Orange::IntType::get(&mod, 16), Orange::BoolType::get(&mod), C(Trunc));
CAST_TEST(TestInt32ToBool, Orange::IntType::get(&mod, 32), Orange::BoolType::get(&mod), C(Trunc));
CAST_TEST(TestInt64ToBool, Orange::IntType::get(&mod, 64), Orange::BoolType::get(&mod), C(Trunc));

// UInt to Bool
CAST_TEST(TestUInt8ToBool,  Orange::UIntType::get(&mod, 8),  Orange::BoolType::get(&mod), C(Trunc));
CAST_TEST(TestUInt16ToBool, Orange::UIntType::get(&mod, 16), Orange::BoolType::get(&mod), C(Trunc));
CAST_TEST(TestUInt32ToBool, Orange::UIntType::get(&mod, 32), Orange::BoolType::get(&mod), C(Trunc));
CAST_TEST(TestUInt64ToBool, Orange::UIntType::get(&mod, 64), Orange::BoolType::get(&mod), C(Trunc));

// Bool to Int
CAST_TEST(TestBoolToInt8,  Orange::BoolType::get(&mod), Orange::IntType::get(&mod, 8),  C(ZExt));
CAST_TEST(TestBoolToInt16, Orange::BoolType::get(&mod), Orange::IntType::get(&mod, 16), C(ZExt));
CAST_TEST(TestBoolToInt32, Orange::BoolType::get(&mod), Orange::IntType::get(&mod, 32), C(ZExt));
CAST_TEST(TestBoolToInt64, Orange::BoolType::get(&mod), Orange::IntType::get(&mod, 64), C(ZExt));

// Bool to UInt
CAST_TEST(TestBoolToUInt8,  Orange::BoolType::get(&mod), Orange::UIntType::get(&mod, 8),  C(ZExt));
CAST_TEST(TestBoolToUInt16, Orange::BoolType::get(&mod), Orange::UIntType::get(&mod, 16), C(ZExt));
CAST_TEST(TestBoolToUInt32, Orange::BoolType::get(&mod), Orange::UIntType::get(&mod, 32), C(ZExt));
CAST_TEST(TestBoolToUInt64, Orange::BoolType::get(&mod), Orange::UIntType::get(&mod, 64), C(ZExt));

// FP to FP.
CAST_TEST(TestFloatToFloat,   Orange::FloatType::get(&mod),  Orange::FloatType::get(&mod),  NO_CAST);
CAST_TEST(TestFloatToDouble,  Orange::FloatType::get(&mod),  Orange::DoubleType::get(&mod), C(FPExt));

CAST_TEST(TestDoubleToDouble, Orange::DoubleType::get(&mod), Orange::DoubleType::get(&mod), NO_CAST);
CAST_TEST(TestDoubleToFloat,  Orange::DoubleType::get(&mod), Orange::FloatType::get(&mod),  C(FPTrunc));

// Float to Int
CAST_TEST(TestFloatToInt8,  Orange::FloatType::get(&mod), Orange::IntType::get(&mod, 8),  C(FPToSI));
CAST_TEST(TestFloatToInt16, Orange::FloatType::get(&mod), Orange::IntType::get(&mod, 16), C(FPToSI));
CAST_TEST(TestFloatToInt32, Orange::FloatType::get(&mod), Orange::IntType::get(&mod, 32), C(FPToSI));
CAST_TEST(TestFloatToInt64, Orange::FloatType::get(&mod), Orange::IntType::get(&mod, 64), C(FPToSI));

// Float to UInt
CAST_TEST(TestFloatToUInt8,  Orange::FloatType::get(&mod), Orange::UIntType::get(&mod, 8),  C(FPToUI));
CAST_TEST(TestFloatToUInt16, Orange::FloatType::get(&mod), Orange::UIntType::get(&mod, 16), C(FPToUI));
CAST_TEST(TestFloatToUInt32, Orange::FloatType::get(&mod), Orange::UIntType::get(&mod, 32), C(FPToUI));
CAST_TEST(TestFloatToUInt64, Orange::FloatType::get(&mod), Orange::UIntType::get(&mod, 64), C(FPToUI));

// Double to Int.
CAST_TEST(TestDoubleToInt8,  Orange::DoubleType::get(&mod), Orange::IntType::get(&mod, 8),  C(FPToSI));
CAST_TEST(TestDoubleToInt16, Orange::DoubleType::get(&mod), Orange::IntType::get(&mod, 16), C(FPToSI));
CAST_TEST(TestDoubleToInt32, Orange::DoubleType::get(&mod), Orange::IntType::get(&mod, 32), C(FPToSI));
CAST_TEST(TestDoubleToInt64, Orange::DoubleType::get(&mod), Orange::IntType::get(&mod, 64), C(FPToSI));

// Double to UInt.
CAST_TEST(TestDoubleToUInt8,  Orange::DoubleType::get(&mod), Orange::UIntType::get(&mod, 8),  C(FPToUI));
CAST_TEST(TestDoubleToUInt16, Orange::DoubleType::get(&mod), Orange::UIntType::get(&mod, 16), C(FPToUI));
CAST_TEST(TestDoubleToUInt32, Orange::DoubleType::get(&mod), Orange::UIntType::get(&mod, 32), C(FPToUI));
CAST_TEST(TestDoubleToUInt64, Orange::DoubleType::get(&mod), Orange::UIntType::get(&mod, 64), C(FPToUI));

// Pointer to Int.
CAST_TEST(TestPointerToInt8,  Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::IntType::get(&mod, 8),  C(PtrToInt));
CAST_TEST(TestPointerToInt16, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::IntType::get(&mod, 16), C(PtrToInt));
CAST_TEST(TestPointerToInt32, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::IntType::get(&mod, 32), C(PtrToInt));
CAST_TEST(TestPointerToInt64, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::IntType::get(&mod, 64), C(PtrToInt));

// Pointer to UInt.
CAST_TEST(TestPointerToUInt8,  Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::UIntType::get(&mod, 8),  C(PtrToInt));
CAST_TEST(TestPointerToUInt16, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::UIntType::get(&mod, 16), C(PtrToInt));
CAST_TEST(TestPointerToUInt32, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::UIntType::get(&mod, 32), C(PtrToInt));
CAST_TEST(TestPointerToUInt64, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::UIntType::get(&mod, 64), C(PtrToInt));

// Pointer to Pointer.
CAST_TEST(TestBoolPointerToBoolPointer, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), NO_CAST);
CAST_TEST(TestBoolPointerToFloatPointer, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::PointerType::get(&mod, Orange::FloatType::get(&mod)), C(BitCast));

// Enums should inherit casts
CAST_TEST(EnumIntToFloat, Orange::EnumType::get(&mod, Orange::IntType::get(&mod, 64)), Orange::FloatType::get(&mod), C(SIToFP));

//////
// Cast tests
//////

// Int to Int
PREC_TEST(CompInt8ToInt8,   Orange::IntType::get(&mod, 8),  Orange::IntType::get(&mod, 8),  EQUAL);
PREC_TEST(CompInt8ToInt16,  Orange::IntType::get(&mod, 8),  Orange::IntType::get(&mod, 16), LOWER_PRECEDENCE);
PREC_TEST(CompInt8ToInt32,  Orange::IntType::get(&mod, 8),  Orange::IntType::get(&mod, 32), LOWER_PRECEDENCE);
PREC_TEST(CompInt8ToInt64,  Orange::IntType::get(&mod, 8),  Orange::IntType::get(&mod, 64), LOWER_PRECEDENCE);
PREC_TEST(CompInt16ToInt8,  Orange::IntType::get(&mod, 16), Orange::IntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompInt16ToInt16, Orange::IntType::get(&mod, 16), Orange::IntType::get(&mod, 16), EQUAL);
PREC_TEST(CompInt16ToInt32, Orange::IntType::get(&mod, 16), Orange::IntType::get(&mod, 32), LOWER_PRECEDENCE	);
PREC_TEST(CompInt16ToInt64, Orange::IntType::get(&mod, 16), Orange::IntType::get(&mod, 64), LOWER_PRECEDENCE);
PREC_TEST(CompInt32ToInt8,  Orange::IntType::get(&mod, 32), Orange::IntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompInt32ToInt16, Orange::IntType::get(&mod, 32), Orange::IntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompInt32ToInt32, Orange::IntType::get(&mod, 32), Orange::IntType::get(&mod, 32), EQUAL);
PREC_TEST(CompInt32ToInt64, Orange::IntType::get(&mod, 32), Orange::IntType::get(&mod, 64), LOWER_PRECEDENCE);
PREC_TEST(CompInt64ToInt8,  Orange::IntType::get(&mod, 64), Orange::IntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompInt64ToInt16, Orange::IntType::get(&mod, 64), Orange::IntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompInt64ToInt32, Orange::IntType::get(&mod, 64), Orange::IntType::get(&mod, 32), HIGHER_PRECEDENCE);
PREC_TEST(CompInt64ToInt64, Orange::IntType::get(&mod, 64), Orange::IntType::get(&mod, 64), EQUAL);

// UInt to UInt
PREC_TEST(CompUInt8ToUInt8,   Orange::UIntType::get(&mod, 8),  Orange::UIntType::get(&mod, 8),  EQUAL);
PREC_TEST(CompUInt8ToUInt16,  Orange::UIntType::get(&mod, 8),  Orange::UIntType::get(&mod, 16), LOWER_PRECEDENCE);
PREC_TEST(CompUInt8ToUInt32,  Orange::UIntType::get(&mod, 8),  Orange::UIntType::get(&mod, 32), LOWER_PRECEDENCE);
PREC_TEST(CompUInt8ToUInt64,  Orange::UIntType::get(&mod, 8),  Orange::UIntType::get(&mod, 64), LOWER_PRECEDENCE);
PREC_TEST(CompUInt16ToUInt8,  Orange::UIntType::get(&mod, 16), Orange::UIntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompUInt16ToUInt16, Orange::UIntType::get(&mod, 16), Orange::UIntType::get(&mod, 16), EQUAL);
PREC_TEST(CompUInt16ToUInt32, Orange::UIntType::get(&mod, 16), Orange::UIntType::get(&mod, 32), LOWER_PRECEDENCE	);
PREC_TEST(CompUInt16ToUInt64, Orange::UIntType::get(&mod, 16), Orange::UIntType::get(&mod, 64), LOWER_PRECEDENCE);
PREC_TEST(CompUInt32ToUInt8,  Orange::UIntType::get(&mod, 32), Orange::UIntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompUInt32ToUInt16, Orange::UIntType::get(&mod, 32), Orange::UIntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompUInt32ToUInt32, Orange::UIntType::get(&mod, 32), Orange::UIntType::get(&mod, 32), EQUAL);
PREC_TEST(CompUInt32ToUInt64, Orange::UIntType::get(&mod, 32), Orange::UIntType::get(&mod, 64), LOWER_PRECEDENCE);
PREC_TEST(CompUInt64ToUInt8,  Orange::UIntType::get(&mod, 64), Orange::UIntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompUInt64ToUInt16, Orange::UIntType::get(&mod, 64), Orange::UIntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompUInt64ToUInt32, Orange::UIntType::get(&mod, 64), Orange::UIntType::get(&mod, 32), HIGHER_PRECEDENCE);
PREC_TEST(CompUInt64ToUInt64, Orange::UIntType::get(&mod, 64), Orange::UIntType::get(&mod, 64), EQUAL);

// Int to UInt. Should SExt to keep negative bit.
PREC_TEST(CompInt8ToUInt8,   Orange::IntType::get(&mod, 8),  Orange::UIntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompInt8ToUInt16,  Orange::IntType::get(&mod, 8),  Orange::UIntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompInt8ToUInt32,  Orange::IntType::get(&mod, 8),  Orange::UIntType::get(&mod, 32), HIGHER_PRECEDENCE);
PREC_TEST(CompInt8ToUInt64,  Orange::IntType::get(&mod, 8),  Orange::UIntType::get(&mod, 64), HIGHER_PRECEDENCE);
PREC_TEST(CompInt16ToUInt8,  Orange::IntType::get(&mod, 16), Orange::UIntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompInt16ToUInt16, Orange::IntType::get(&mod, 16), Orange::UIntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompInt16ToUInt32, Orange::IntType::get(&mod, 16), Orange::UIntType::get(&mod, 32), HIGHER_PRECEDENCE);
PREC_TEST(CompInt16ToUInt64, Orange::IntType::get(&mod, 16), Orange::UIntType::get(&mod, 64), HIGHER_PRECEDENCE);
PREC_TEST(CompInt32ToUInt8,  Orange::IntType::get(&mod, 32), Orange::UIntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompInt32ToUInt16, Orange::IntType::get(&mod, 32), Orange::UIntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompInt32ToUInt32, Orange::IntType::get(&mod, 32), Orange::UIntType::get(&mod, 32), HIGHER_PRECEDENCE);
PREC_TEST(CompInt32ToUInt64, Orange::IntType::get(&mod, 32), Orange::UIntType::get(&mod, 64), HIGHER_PRECEDENCE);
PREC_TEST(CompInt64ToUInt8,  Orange::IntType::get(&mod, 64), Orange::UIntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompInt64ToUInt16, Orange::IntType::get(&mod, 64), Orange::UIntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompInt64ToUInt32, Orange::IntType::get(&mod, 64), Orange::UIntType::get(&mod, 32), HIGHER_PRECEDENCE);
PREC_TEST(CompInt64ToUInt64, Orange::IntType::get(&mod, 64), Orange::UIntType::get(&mod, 64), HIGHER_PRECEDENCE);

// UInt to Int. Should ZExt.
PREC_TEST(CompUInt8ToInt8,   Orange::UIntType::get(&mod, 8),  Orange::IntType::get(&mod, 8),  LOWER_PRECEDENCE);
PREC_TEST(CompUInt8ToInt16,  Orange::UIntType::get(&mod, 8),  Orange::IntType::get(&mod, 16), LOWER_PRECEDENCE);
PREC_TEST(CompUInt8ToInt32,  Orange::UIntType::get(&mod, 8),  Orange::IntType::get(&mod, 32), LOWER_PRECEDENCE);
PREC_TEST(CompUInt8ToInt64,  Orange::UIntType::get(&mod, 8),  Orange::IntType::get(&mod, 64), LOWER_PRECEDENCE);
PREC_TEST(CompUInt16ToInt8,  Orange::UIntType::get(&mod, 16), Orange::IntType::get(&mod, 8),  LOWER_PRECEDENCE);
PREC_TEST(CompUInt16ToInt16, Orange::UIntType::get(&mod, 16), Orange::IntType::get(&mod, 16), LOWER_PRECEDENCE);
PREC_TEST(CompUInt16ToInt32, Orange::UIntType::get(&mod, 16), Orange::IntType::get(&mod, 32), LOWER_PRECEDENCE);
PREC_TEST(CompUInt16ToInt64, Orange::UIntType::get(&mod, 16), Orange::IntType::get(&mod, 64), LOWER_PRECEDENCE);
PREC_TEST(CompUInt32ToInt8,  Orange::UIntType::get(&mod, 32), Orange::IntType::get(&mod, 8),  LOWER_PRECEDENCE);
PREC_TEST(CompUInt32ToInt16, Orange::UIntType::get(&mod, 32), Orange::IntType::get(&mod, 16), LOWER_PRECEDENCE);
PREC_TEST(CompUInt32ToInt32, Orange::UIntType::get(&mod, 32), Orange::IntType::get(&mod, 32), LOWER_PRECEDENCE);
PREC_TEST(CompUInt32ToInt64, Orange::UIntType::get(&mod, 32), Orange::IntType::get(&mod, 64), LOWER_PRECEDENCE);
PREC_TEST(CompUInt64ToInt8,  Orange::UIntType::get(&mod, 64), Orange::IntType::get(&mod, 8),  LOWER_PRECEDENCE);
PREC_TEST(CompUInt64ToInt16, Orange::UIntType::get(&mod, 64), Orange::IntType::get(&mod, 16), LOWER_PRECEDENCE);
PREC_TEST(CompUInt64ToInt32, Orange::UIntType::get(&mod, 64), Orange::IntType::get(&mod, 32), LOWER_PRECEDENCE);
PREC_TEST(CompUInt64ToInt64, Orange::UIntType::get(&mod, 64), Orange::IntType::get(&mod, 64), LOWER_PRECEDENCE);

// Int to Float.
PREC_TEST(CompInt8ToFloat,  Orange::IntType::get(&mod, 8),  Orange::FloatType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompInt16ToFloat, Orange::IntType::get(&mod, 16), Orange::FloatType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompInt32ToFloat, Orange::IntType::get(&mod, 32), Orange::FloatType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompInt64ToFloat, Orange::IntType::get(&mod, 64), Orange::FloatType::get(&mod), LOWER_PRECEDENCE);

// UInt to Float.
PREC_TEST(CompUInt8ToFloat,  Orange::UIntType::get(&mod, 8),  Orange::FloatType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompUInt16ToFloat, Orange::UIntType::get(&mod, 16), Orange::FloatType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompUInt32ToFloat, Orange::UIntType::get(&mod, 32), Orange::FloatType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompUInt64ToFloat, Orange::UIntType::get(&mod, 64), Orange::FloatType::get(&mod), LOWER_PRECEDENCE);

// Int to Double.
PREC_TEST(CompInt8ToDouble,  Orange::IntType::get(&mod, 8),  Orange::DoubleType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompInt16ToDouble, Orange::IntType::get(&mod, 16), Orange::DoubleType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompInt32ToDouble, Orange::IntType::get(&mod, 32), Orange::DoubleType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompInt64ToDouble, Orange::IntType::get(&mod, 64), Orange::DoubleType::get(&mod), LOWER_PRECEDENCE);

// UInt to Double.
PREC_TEST(CompUInt8ToDouble,  Orange::UIntType::get(&mod, 8),  Orange::DoubleType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompUInt16ToDouble, Orange::UIntType::get(&mod, 16), Orange::DoubleType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompUInt32ToDouble, Orange::UIntType::get(&mod, 32), Orange::DoubleType::get(&mod), LOWER_PRECEDENCE);
PREC_TEST(CompUInt64ToDouble, Orange::UIntType::get(&mod, 64), Orange::DoubleType::get(&mod), LOWER_PRECEDENCE);

// Int to Pointer.
PREC_TEST(CompInt8ToPointer,  Orange::IntType::get(&mod, 8),  Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), HIGHER_PRECEDENCE);
PREC_TEST(CompInt16ToPointer, Orange::IntType::get(&mod, 16), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), HIGHER_PRECEDENCE);
PREC_TEST(CompInt32ToPointer, Orange::IntType::get(&mod, 32), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), HIGHER_PRECEDENCE);
PREC_TEST(CompInt64ToPointer, Orange::IntType::get(&mod, 64), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), HIGHER_PRECEDENCE);

// UInt to Pointer.
PREC_TEST(CompUInt8ToPointer,  Orange::UIntType::get(&mod, 8),  Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), HIGHER_PRECEDENCE);
PREC_TEST(CompUInt16ToPointer, Orange::UIntType::get(&mod, 16), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), HIGHER_PRECEDENCE);
PREC_TEST(CompUInt32ToPointer, Orange::UIntType::get(&mod, 32), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), HIGHER_PRECEDENCE);
PREC_TEST(CompUInt64ToPointer, Orange::UIntType::get(&mod, 64), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), HIGHER_PRECEDENCE);

// Int to Bool
PREC_TEST(CompInt8ToBool,  Orange::IntType::get(&mod, 8),  Orange::BoolType::get(&mod), HIGHER_PRECEDENCE);
PREC_TEST(CompInt16ToBool, Orange::IntType::get(&mod, 16), Orange::BoolType::get(&mod), HIGHER_PRECEDENCE);
PREC_TEST(CompInt32ToBool, Orange::IntType::get(&mod, 32), Orange::BoolType::get(&mod), HIGHER_PRECEDENCE);
PREC_TEST(CompInt64ToBool, Orange::IntType::get(&mod, 64), Orange::BoolType::get(&mod), HIGHER_PRECEDENCE);

// UInt to Bool
PREC_TEST(CompUInt8ToBool,  Orange::UIntType::get(&mod, 8),  Orange::BoolType::get(&mod), HIGHER_PRECEDENCE);
PREC_TEST(CompUInt16ToBool, Orange::UIntType::get(&mod, 16), Orange::BoolType::get(&mod), HIGHER_PRECEDENCE);
PREC_TEST(CompUInt32ToBool, Orange::UIntType::get(&mod, 32), Orange::BoolType::get(&mod), HIGHER_PRECEDENCE);
PREC_TEST(CompUInt64ToBool, Orange::UIntType::get(&mod, 64), Orange::BoolType::get(&mod), HIGHER_PRECEDENCE);

// Bool to Int
PREC_TEST(CompBoolToInt8,  Orange::BoolType::get(&mod), Orange::IntType::get(&mod, 8),  LOWER_PRECEDENCE);
PREC_TEST(CompBoolToInt16, Orange::BoolType::get(&mod), Orange::IntType::get(&mod, 16), LOWER_PRECEDENCE);
PREC_TEST(CompBoolToInt32, Orange::BoolType::get(&mod), Orange::IntType::get(&mod, 32), LOWER_PRECEDENCE);
PREC_TEST(CompBoolToInt64, Orange::BoolType::get(&mod), Orange::IntType::get(&mod, 64), LOWER_PRECEDENCE);

// Bool to UInt
PREC_TEST(CompBoolToUInt8,  Orange::BoolType::get(&mod), Orange::UIntType::get(&mod, 8),  LOWER_PRECEDENCE);
PREC_TEST(CompBoolToUInt16, Orange::BoolType::get(&mod), Orange::UIntType::get(&mod, 16), LOWER_PRECEDENCE);
PREC_TEST(CompBoolToUInt32, Orange::BoolType::get(&mod), Orange::UIntType::get(&mod, 32), LOWER_PRECEDENCE);
PREC_TEST(CompBoolToUInt64, Orange::BoolType::get(&mod), Orange::UIntType::get(&mod, 64), LOWER_PRECEDENCE);


// FP to FP.
PREC_TEST(CompFloatToFloat,   Orange::FloatType::get(&mod),  Orange::FloatType::get(&mod),  EQUAL);
PREC_TEST(CompFloatToDouble,  Orange::FloatType::get(&mod),  Orange::DoubleType::get(&mod), LOWER_PRECEDENCE);

PREC_TEST(CompDoubleToDouble, Orange::DoubleType::get(&mod), Orange::DoubleType::get(&mod), EQUAL);
PREC_TEST(CompDoubleToFloat,  Orange::DoubleType::get(&mod), Orange::FloatType::get(&mod),  HIGHER_PRECEDENCE);

// Float to Int
PREC_TEST(CompFloatToInt8,  Orange::FloatType::get(&mod), Orange::IntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompFloatToInt16, Orange::FloatType::get(&mod), Orange::IntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompFloatToInt32, Orange::FloatType::get(&mod), Orange::IntType::get(&mod, 32), HIGHER_PRECEDENCE);
PREC_TEST(CompFloatToInt64, Orange::FloatType::get(&mod), Orange::IntType::get(&mod, 64), HIGHER_PRECEDENCE);

// Float to UInt
PREC_TEST(CompFloatToUInt8,  Orange::FloatType::get(&mod), Orange::UIntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompFloatToUInt16, Orange::FloatType::get(&mod), Orange::UIntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompFloatToUInt32, Orange::FloatType::get(&mod), Orange::UIntType::get(&mod, 32), HIGHER_PRECEDENCE);
PREC_TEST(CompFloatToUInt64, Orange::FloatType::get(&mod), Orange::UIntType::get(&mod, 64), HIGHER_PRECEDENCE);

// Double to Int.
PREC_TEST(CompDoubleToInt8,  Orange::DoubleType::get(&mod), Orange::IntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompDoubleToInt16, Orange::DoubleType::get(&mod), Orange::IntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompDoubleToInt32, Orange::DoubleType::get(&mod), Orange::IntType::get(&mod, 32), HIGHER_PRECEDENCE);
PREC_TEST(CompDoubleToInt64, Orange::DoubleType::get(&mod), Orange::IntType::get(&mod, 64), HIGHER_PRECEDENCE);

// Double to UInt.
PREC_TEST(CompDoubleToUInt8,  Orange::DoubleType::get(&mod), Orange::UIntType::get(&mod, 8),  HIGHER_PRECEDENCE);
PREC_TEST(CompDoubleToUInt16, Orange::DoubleType::get(&mod), Orange::UIntType::get(&mod, 16), HIGHER_PRECEDENCE);
PREC_TEST(CompDoubleToUInt32, Orange::DoubleType::get(&mod), Orange::UIntType::get(&mod, 32), HIGHER_PRECEDENCE);
PREC_TEST(CompDoubleToUInt64, Orange::DoubleType::get(&mod), Orange::UIntType::get(&mod, 64), HIGHER_PRECEDENCE);

// Pointer to Int.
PREC_TEST(CompPointerToInt8,  Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::IntType::get(&mod, 8),  LOWER_PRECEDENCE);
PREC_TEST(CompPointerToInt16, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::IntType::get(&mod, 16), LOWER_PRECEDENCE);
PREC_TEST(CompPointerToInt32, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::IntType::get(&mod, 32), LOWER_PRECEDENCE);
PREC_TEST(CompPointerToInt64, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::IntType::get(&mod, 64), LOWER_PRECEDENCE);

// Pointer to UInt.
PREC_TEST(CompPointerToUInt8,  Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::UIntType::get(&mod, 8),  LOWER_PRECEDENCE);
PREC_TEST(CompPointerToUInt16, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::UIntType::get(&mod, 16), LOWER_PRECEDENCE);
PREC_TEST(CompPointerToUInt32, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::UIntType::get(&mod, 32), LOWER_PRECEDENCE);
PREC_TEST(CompPointerToUInt64, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::UIntType::get(&mod, 64), LOWER_PRECEDENCE);

// Pointer to Pointer.
PREC_TEST(CompBoolPointerToBoolPointer, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), EQUAL);
PREC_TEST(CompBoolPointerToFloatPointer, Orange::PointerType::get(&mod, Orange::BoolType::get(&mod)), Orange::PointerType::get(&mod, Orange::FloatType::get(&mod)), INCOMPATIBLE);


RUN_TESTS();