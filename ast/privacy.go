package ast

type PrivacyLevel int8

const (
	PrivacyDefault PrivacyLevel = iota
	PrivacyPublic
	PrivacyPackage
	PrivacyProtected
	PrivacyPrivate
)
