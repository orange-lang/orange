# Orange
Orange is a programming language with the goal of being able to write fast, efficient code as fast as possible. 
It uses LLVM to generate native code. You can look inside the `test/` folder to get examples of how Orange works.

# Status 
Orange is still very much a work in progress. The `remake` branch is intended to be a full re-write with a 
focus on compiler errors and warnings and to support either running an `.or` file as JIT directly or compiling to
native. No work will be done in the `master` branch until remake is finished and merged back into master.

# Hello World
At the moment, Orange has no standard library, so you'll need to link against C library functions to do more 
complicated tasks:

    extern int32 printf(char *s, ...)
    printf("Hello, world!\n")

# Building 
Orange currently requires Boost, Flex, Bison, CMake, and if you're on Windows, mingw-w64. 
The most functional compiler will be in the `master` branch, which should be able to pass all but one test.

