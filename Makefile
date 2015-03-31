SOURCES=main.o parser.o lexer.o AST.o
CXXFLAGS=--std=c++11 `llvm-config --cxxflags` -fexceptions -Wno-unused -O3 -Wno-deprecated-register


all: oc

oc: $(SOURCES) parser.cc lexer.cc 
	clang++ $(CXXFLAGS) `llvm-config --cxxflags --ldflags --system-libs --libs core native` -o oc $(SOURCES)

lexer.cc: lexer.l 
	flex -o lexer.cc lexer.l

parser.cc: parser.y
	bison -d -o parser.cc parser.y

test: oc
	./oc test/a.or

%.o: %.cc %.h
	clang++ $(CXXFLAGS) -c $<

%.o: %.cc 
	clang++ $(CXXFLAGS) -c $<

clean:
	rm -f *.o lexer.cc parser.cc oc

.PHONY: clean all test