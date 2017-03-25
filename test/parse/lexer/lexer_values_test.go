package test

import (
	"github.com/orange-lang/orange/parse/lexer"
	"github.com/orange-lang/orange/parse/lexer/token"

	. "github.com/onsi/ginkgo"
	. "github.com/onsi/ginkgo/extensions/table"
	. "github.com/onsi/gomega"
)

var _ = Describe("Constants", func() {
	Describe("Strings", func() {
		DescribeTable("will be lexed when", expectToken,
			Entry("a string is provided", "\"foobar\"", token.StringVal),
			Entry("a has an escaped double quote", "\"fo\\\"obar\"", token.StringVal),
			Entry("a has a newline", "\"foo\\nbar\"", token.StringVal),
			Entry("a has a tab", "\"foo\\tbar\"", token.StringVal),
			Entry("a has a backslash", "\"foo\\\\bar\"", token.StringVal),
		)

		DescribeTable("will have the correct value when", expectValue,
			Entry("a string is provided", "\"foobar\"", "foobar"),
			Entry("a has an escaped double quote", "\"fo\\\"obar\"", "fo\"obar"),
			Entry("a has a newline", "\"foo\\nbar\"", "foo\nbar"),
			Entry("a has a tab", "\"foo\\tbar\"", "foo\tbar"),
			Entry("a has a backslash", "\"foo\\\\bar\"", "foo\\bar"),
		)
	})

	Describe("Chars", func() {
		DescribeTable("will have the right token when", expectToken,
			Entry("one is provided", "'c'", token.CharVal),
			Entry("it's a newline", "'\n'", token.CharVal),
			Entry("it's a tab", "'\t'", token.CharVal),
			Entry("it's a backslash", "'\\\\'", token.CharVal),
			Entry("it's a single quote", "'\\''", token.CharVal),
		)

		DescribeTable("will have the right value when", expectValue,
			Entry("one is provided", "'c'", "c"),
			Entry("it's a newline", "'\n'", "\n"),
			Entry("it's a tab", "'\t'", "\t"),
			Entry("it's a backslash", "'\\\\'", "\\"),
			Entry("it's a single quote", "'\\''", "'"),
		)
	})

	Describe("Booleans", func() {
		DescribeTable("will have the right token when", expectToken,
			Entry("it's true", "true", token.BoolVal),
			Entry("it's false", "false", token.BoolVal),
		)

		DescribeTable("will have the right value when", expectValue,
			Entry("it's true", "true", "true"),
			Entry("it's false", "false", "false"),
		)
	})

	Describe("Comments", func() {
		DescribeTable("will be ignored when it's a", expectToken,
			Entry("single line comment", "// Testing \n5", token.IntVal),
			Entry("block comment", "/*Testing*/5", token.IntVal),
			Entry("multi-line comment", "/*Testing\nComments*/5", token.IntVal),
			Entry("nested block comment", "/*testing/*comments*/*/5", token.IntVal),
		)
	})
})

var _ = Describe("Numbers", func() {
	Describe("Whitespace", func() {
		DescribeTable("should be ignored when",
			func(input string, expected token.Token) {
				expectToken(input, expected)
			},
			Entry("it exists", "   		  1234567890", token.IntVal),
		)
	})

	Describe("as the object in a method", func() {
		DescribeTable("should ignore the period when", expectToken,
			Entry("the number is zero", "0.test(5)", token.IntVal),
			Entry("the number has a suffix", "5i16.test(5)", token.Int16Val),
			Entry("radix != 10", "0xABC.test(5)", token.UIntVal),
		)
	})

	Describe("types", func() {
		DescribeTable("should inherit the default type when", expectToken,
			Entry("it's a decimal", "1234567890", token.IntVal),
			Entry("it's a floating-point", "12345.06789", token.DoubleVal),
			Entry("it's a binary", "0b010101", token.UIntVal),
			Entry("it's an octal", "0o01234567", token.UIntVal),
			Entry("it's a hexadecimal", "0xabcdef", token.UIntVal),
			Entry("it's a hexadecimal 0-9", "0x0123456789", token.UIntVal),
		)

		DescribeTable("should inherit type from suffixes when", expectToken,
			Entry("it's a decimal i", "123i", token.IntVal),
			Entry("it's a decimal i8", "123i8", token.Int8Val),
			Entry("it's a decimal i16", "123i16", token.Int16Val),
			Entry("it's a decimal i32", "123i32", token.Int32Val),
			Entry("it's a decimal i64", "123i64", token.Int64Val),
			Entry("it's a decimal u", "123u", token.UIntVal),
			Entry("it's a decimal u8", "123u8", token.UInt8Val),
			Entry("it's a decimal u16", "123u16", token.UInt16Val),
			Entry("it's a decimal u32", "123u32", token.UInt32Val),
			Entry("it's a decimal u64", "123u64", token.UInt64Val),
			Entry("it's a decimal f", "123f", token.FloatVal),
			Entry("it's a decimal d", "123d", token.DoubleVal),
			Entry("it's a binary u", "0b0110u", token.UIntVal),
			Entry("it's a binary u8", "0b0110u8", token.UInt8Val),
			Entry("it's a binary u16", "0b0110u16", token.UInt16Val),
			Entry("it's a binary u32", "0b0110u32", token.UInt32Val),
			Entry("it's a binary u64", "0b0110u64", token.UInt64Val),
			Entry("it's a octal u", "0o75u", token.UIntVal),
			Entry("it's a octal u8", "0o75u8", token.UInt8Val),
			Entry("it's a octal u16", "0o75u16", token.UInt16Val),
			Entry("it's a octal u32", "0o75u32", token.UInt32Val),
			Entry("it's a octal u64", "0o75u64", token.UInt64Val),
			Entry("it's a hexadecimal u", "0xADu", token.UIntVal),
			Entry("it's a hexadecimal u8", "0xADu8", token.UInt8Val),
			Entry("it's a hexadecimal u16", "0xADu16", token.UInt16Val),
			Entry("it's a hexadecimal u32", "0xADu32", token.UInt32Val),
			Entry("it's a hexadecimal u64", "0xADu64", token.UInt64Val),
			Entry("it's a floating-point f", "1.0f", token.FloatVal),
		)

		DescribeTable("should not allow invalid suffix combinations when", expectError,
			Entry("it's a binary with i", "0b0110i"),
			Entry("it's a binary with i8", "0b0110i8"),
			Entry("it's a binary with i16", "0b0110i16"),
			Entry("it's a binary with i32", "0b0110i32"),
			Entry("it's a binary with i64", "0b0110i64"),
			Entry("it's a octal with i", "0o75i"),
			Entry("it's a octal with i8", "0o75i8"),
			Entry("it's a octal with i16", "0o75i16"),
			Entry("it's a octal with i32", "0o75i32"),
			Entry("it's a octal with i64", "0o75i64"),
			Entry("it's a hexadecimal with i", "0xADi"),
			Entry("it's a hexadecimal with i8", "0xADi8"),
			Entry("it's a hexadecimal with i16", "0xADi16"),
			Entry("it's a hexadecimal with i32", "0xADi32"),
			Entry("it's a hexadecimal with i64", "0xADi64"),
			Entry("it's a floating-point with i", "1.0i"),
			Entry("it's a floating-point with i8", "1.0i8"),
			Entry("it's a floating-point with i16", "1.0i16"),
			Entry("it's a floating-point with i32", "1.0i32"),
			Entry("it's a floating-point with i64", "1.0i64"),
			Entry("it's a floating-point with u", "1.0u"),
			Entry("it's a floating-point with u8", "1.0u8"),
			Entry("it's a floating-point with u16", "1.0u16"),
			Entry("it's a floating-point with u32", "1.0u32"),
			Entry("it's a floating-point with u64", "1.0u64"),
		)
	})

	DescribeTable("should allow underscores", expectValue,
		Entry("one underscore", "0b11_11", "15"),
		Entry("multiple underscores", "0b11___1_1", "15"),
		Entry("underscore at end", "0b1111_", "15"),
	)

	Describe("values", func() {
		DescribeTable("should parse the correct value, regardless of radix when", expectValue,
			Entry("it's decimal", "1234", "1234"),
			Entry("it's binary", "0b1111", "15"),
			Entry("it's octal", "0o1234", "668"),
			Entry("it's hexadecimal", "0xAD", "173"),
		)

		DescribeTable("should allow for leading zeroes after a prefix when", expectValue,
			Entry("it's binary", "0b001111", "15"),
			Entry("it's octal", "0o001234", "668"),
			Entry("it's hexadecimal", "0x00AD", "173"),
			Entry("it's floating point", "0.012345", "0.012345"),
		)

		DescribeTable("should parse the correct value when a suffix is supplied when", expectValue,
			Entry("it's decimal", "1234i32", "1234"),
			Entry("it's binary", "0b1111u32", "15"),
			Entry("it's octal", "0o1234u32", "668"),
			Entry("it's hexadecimal", "0xADu32", "173"),
		)

		DescribeTable("should not allow for invalid digits beyond the radix when", expectError,
			Entry("it's binary", "0b0101201"),
			Entry("it's octal", "0o12349"),
		)
	})
})

func getLexer(input string) lexer.Lexer {
	return lexer.Lexer{Stream: &lexer.StringRuneStream{Source: input}}
}

func expectError(input string) {
	l := lexer.Lexer{Stream: &lexer.StringRuneStream{
		Source: input,
	}}

	_, err := l.Next()
	Expect(err).ToNot(BeNil())
}

func expectValue(input string, expect string) {
	l := lexer.Lexer{Stream: &lexer.StringRuneStream{
		Source: input,
	}}

	next, err := l.Next()

	Expect(err).To(BeNil())
	Expect(next.Value).To(Equal(expect))
}

func expectToken(input string, expect token.Token) {
	l := lexer.Lexer{Stream: &lexer.StringRuneStream{
		Source: input,
	}}

	next, err := l.Next()

	Expect(err).To(BeNil())
	Expect(next.Token).To(equalToken(expect))
}
