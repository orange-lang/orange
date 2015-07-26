# Orange [![Build Status](https://travis-ci.org/orange-lang/orange.svg?branch=master)](https://travis-ci.org/orange-lang/orange)
Orange is a systems programming language made to be as powerful as C++ with none of the headache. It aims to be very producitve by baking the most important low- and high-level features directly into the langauge, instead of dealing with them through obtuse function calls. 

# Status 

Orange is still under development and in the design phase; a lot of planned features are not yet implemented. Check the [TODO](/TODO.md) to see what needs to be done.

# Hello World
At the moment, Orange has no standard library, so you'll need to link against C library functions to do more 
complicated tasks:

    # test.or
    extern printf(char *s, ...) -> int32

    for (var i = 0; i < 10; i++) 
        printf("Hello, world %d!\n", i)
    end
    
Run directly with `orange run test.or` or build a native binary with `orange build test.or` and run with `./a.out`. 
    
# Resources

* [Language Guide](http://orange-lang.gitbooks.io/orange-docs/content/) ([Github](https://github.com/orange-lang/orange-docs))
* [Orange TODO features](/TODO.md)
* [Tests](/test/)

# Building 
Building on OS X and Linux should be pretty simple; first install CMake from source or using a package manager like [homebrew](http://brew.sh) for OS X. After CMake is installed, building is as easy as:

```sh 
$ # cd to the orange source folder 
$ git submodule init && git submodule update
$ mkdir build-orange && cd build-orange 
$ cmake ..
$ make all install
``` 

CMake will try to find LLVM 3.6 on your system; if it is not installed, it will build it from source. 

[Building on Windows](http://docs.orange-lang.org/installation/installing_on_windows.html) takes a bit more effort.

# Community

Orange has an IRC channel on [irc.freenode.net](irc.freenode.net) at #orange-lang. Come say hi! Feel free to open any issues on Github about questions, suggestions, or bugs. We also have a [Google Group](https://groups.google.com/forum/#!forum/orange-lang) open to the public. 
