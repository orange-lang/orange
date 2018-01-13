package analysis

import (
	. "github.com/onsi/ginkgo"
	. "github.com/onsi/gomega"

	"testing"
)

func TestAnalysis(t *testing.T) {
	RegisterFailHandler(Fail)
	RunSpecs(t, "Analysis Suite")
}
