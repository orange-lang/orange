package lexer

func isFloatingPointSuffix(r rune) bool {
	return r == 'f' || r == 'd'
}

// validSuffixStarter checks to see that the rune would be the first
// character of a suffix
func validSuffixStarter(r rune) bool {
	return r == 'i' || r == 'f' || r == 'd' || r == 'u'
}
