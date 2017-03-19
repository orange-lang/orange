package lexer

func isHexDigit(r rune) bool {
	return (r >= '0' && r <= '9') || (r >= 'a' && r <= 'f') ||
		(r >= 'A' && r <= 'F')
}

func validStringForBase(n string, b int) bool {
	for _, c := range n {
		if c == '.' && b == 10 {
			continue
		}

		if !validRuneForBase(c, b) {
			return false
		}
	}

	return true
}

func validRuneForBase(r rune, b int) bool {
	if b == 2 {
		return r == '0' || r == '1'
	} else if b == 8 {
		return r >= '0' && r <= '7'
	} else if b == 10 {
		return r >= '0' && r <= '9'
	} else if b == 16 {
		return isHexDigit(r)
	}

	return false
}
