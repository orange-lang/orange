SOURCES=main.o lexer.o parser.o codegen.o
CXXFLAGS=--std=c++11 `llvm-config --cxxflags` -fexceptions -Wno-unused -O3


all: oc

oc: $(SOURCES)
	clang++ $(CXXFLAGS) `llvm-config --cxxflags --ldflags --system-libs --libs core native` -o oc $(SOURCES)

test: oc
	./oc test/a.or

%.o: %.cc %.h
	clang++ $(CXXFLAGS) -c $<

%.o: %.cc 
	clang++ $(CXXFLAGS) -c $<

clean:
	rm -f *.o oc

.PHONY: clean all test