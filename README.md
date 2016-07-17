# Orange

[![Join the chat at https://gitter.im/orange-lang/orange](https://badges.gitter.im/orange-lang/orange.svg)](https://gitter.im/orange-lang/orange?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Orange is a statically-typed, multi-paradigm (imperative, object-oriented, generic) systems programming language that tries to allow for rapid development without sacrificing speed or control. It's perfect for both high-and low-level applications.

# Status

Orange is still under active development; you're currently viewing a branch that is a complete re-architecture of the Orange compiler that allows for easier development and expansion. It also houses an updated version of the Orange language specification that envisions the language to be more expressive and C# like.

Linux/OS X  | Windows
------------- | -------------
[![Build Status](https://travis-ci.org/orange-lang/orange.svg?branch=rev-2)](https://travis-ci.org/orange-lang/orange) | [![Build status](https://ci.appveyor.com/api/projects/status/r4y46n573riuqfv1/branch/rev-2?svg=true)](https://ci.appveyor.com/project/rfratto/orange-9no7j/branch/rev-2)

# Resources

* [Language Guide](http://docs.orange-lang.org/v/rev-2/) ([Github](https://github.com/orange-lang/orange-docs/tree/rev-2))
* [Compiler Internal Reference](http://docs.orange-lang.org/v/rev-2/internals/)

# Building
Building on OS X and Linux should be straightforward. Make sure git and CMake are installed and then run the following commands:

```sh
$ git clone https://github.com/orange-lang/orange.git
$ cd orange
$ git submodule update --init
$ mkdir build-orange && cd build-orange
$ cmake ..
$ make all install
```

Building on Windows is supported through [MSYS2](https://msys2.github.io)

# Community

Orange has a [Gitter](https://gitter.im/orange-lang/orange?utm_source=share-link&utm_medium=link&utm_campaign=share-link). Come say hi! Feel free to open any issues on Github about questions, suggestions, or bugs. We also have a [Google Group](https://groups.google.com/forum/#!forum/orange-lang) open to the public.
