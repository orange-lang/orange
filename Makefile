SOURCES=main.o lexer.o parser.o
CXXFLAGS=--std=c++11

all: oc

oc: $(SOURCES)
	clang++ $(CXXFLAGS) -o oc $(SOURCES)

test: oc
	./oc test/a.or

%.o: %.cc %.h
	clang++ $(CXXFLAGS) -c $<

clean:
	rm -f *.o oc

.PHONY: clean all test