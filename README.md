# Orange
Orange is a programming language with the goal of being able to write fast, efficient code as fast as possible. 
It uses LLVM to generate native code. You can look inside the `test/` folder to get examples of how Orange works.

# Status 
Orange is still very much a work in progress. At the moment, Orange supports compiling JIT or to a native binary on OS X and Linux. Windows support is coming soon. 

# Hello World
At the moment, Orange has no standard library, so you'll need to link against C library functions to do more 
complicated tasks:

    extern int32 printf(char *s, ...)

    for (i = 0; i < 10; i++) 
        printf("Hello, world %d!\n", i)
    end

You can see more examples of Orange in the `test/` folder. 

# Building 
Orange currently requires Boost, Flex, Bison, CMake, and if you're on Windows, mingw-w64. Windows support is spotty at the moment and is a work in progress (running JIT *should* work.)
