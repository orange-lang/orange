# Orange  

[![Join the chat at https://gitter.im/orange-lang/orange](https://badges.gitter.im/orange-lang/orange.svg)](https://gitter.im/orange-lang/orange?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Orange is a statically typed, multi-paradigm (imperative, object-oriented, reflective) systems programming language with focus on high productivity, features for DRY code, and a smooth syntax.

# Status

Orange is still under development and in the design phase; a lot of planned features are not yet implemented, and syntax may change until the language hits an initial release.

Linux/OS X  | Windows
------------- | -------------
[![Build Status](https://travis-ci.org/orange-lang/orange.svg?branch=master)](https://travis-ci.org/orange-lang/orange) | [![Build status](https://ci.appveyor.com/api/projects/status/r4y46n573riuqfv1/branch/master?svg=true)](https://ci.appveyor.com/project/rfratto/orange-9no7j/branch/master)

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

Orange has a [Gitter](https://gitter.im/orange-lang/orange?utm_source=share-link&utm_medium=link&utm_campaign=share-link). Come say hi! Feel free to open any issues on Github about questions, suggestions, or bugs. We also have a [Google Group](https://groups.google.com/forum/#!forum/orange-lang) open to the public.
