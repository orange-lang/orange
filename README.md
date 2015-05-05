# Orange
Orange is a programming language with the goal of being able to write fast, efficient code as fast as possible. 
It uses LLVM to generate native code. You can look inside the `test/` folder to get examples of how Orange works.

# Status 
Orange is still very much a work in progress. At the moment, Orange supports compiling JIT or to a native binary with OS X, Linux, and Windows.

# Hello World
At the moment, Orange has no standard library, so you'll need to link against C library functions to do more 
complicated tasks:

    extern int32 printf(char *s, ...)

    for (i = 0; i < 10; i++) 
        printf("Hello, world %d!\n", i)
    end

You can see more examples of Orange in the `test/` folder. 

# Building on OS X and Linux
Orange currently requires Boost, Flex, Bison, CMake, and LLVM, which can all be installed using your favorite package manager. Building is as easy as:

```sh 
$ mkdir build-orange && cd build-orange 
$ cmake ../orange
$ make all install
``` 

# Building on Windows 

Windows takes a bit of extra work. First, download [MSYS2](http://msys2.github.io/) and use the installer. 

Next, from the MSYS2 terminal, install all the required toolchains:

For 32-bit machines:

```sh
$ pacman -S mingw-w64-i686-toolchain
$ pacman -S mingw-w64-i686-cmake
$ pacman -S mingw-w64-i686-boost
$ pacman -S base-devel
```

For 64-bit machines:

```sh
$ pacman -S mingw-w64-x86_64-toolchain
$ pacman -S mingw-w64-x86_64-cmake
$ pacman -S mingw-w64-x86_64-boost
$ pacman -S base-devel
```

Next, download and install LLVM using MSYS2. If the installation directory with CMake is left unchanged, make sure the MSYS2 shell is run as Administrator, as it will install to `C:/Program Files (x86)`. 

```sh
$ mkdir build-llvm && cd build-llvm
$ cmake ../llvm-src -G "MSYS Makefiles"
$ make all install # this will take a while! 
``` 

Finally, you can build and use Orange.

```sh 
$ mkdir build-orange && cd build-orange 
$ cmake ../orange -G "MSYS Makefiles"
$ make all
``` 

At the time of writing, installing to `C:/Program Files (x86)` won't work as `orange.exe` depends on some DLLs from MSYS2 and MINGW. You'll have to run `orange.exe` from inside of the MSYS2 shell. However, any program built using Orange will work outside of the MSYS2 shell. 