# Orange

[![Join the chat at https://gitter.im/orange-lang/orange](https://badges.gitter.im/orange-lang/orange.svg)](https://gitter.im/orange-lang/orange?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Orange is a statically typed, multi-paradigm (imperative, object-oriented) systems programming language with a focus on high productivity and extendability.

# Goals

- _Be Productive_. Provide a simple syntax for writing code quickly and make it easy to download and install project dependencies. Provide strict type checking to make sure basic type errors can’t happen.
- _Be Extendible_. Allow developers to extend new interfaces to existing types, and allow for creating/downloading compiler extensions that can add new language features and code checks.
- _Be Flexible_. Combine the extendibility and productivity to make Orange suitable for any kind of development, from embedded programming to high-level applications like web servers.

# Status

Linux/OS X  | Windows
------------- | -------------
[![Build Status](https://travis-ci.org/orange-lang/orange.svg?branch=master)](https://travis-ci.org/orange-lang/orange) | [![Build status](https://ci.appveyor.com/api/projects/status/r4y46n573riuqfv1/branch/master?svg=true)](https://ci.appveyor.com/project/rfratto/orange-9no7j/branch/master)

# Note

The language has been redesigned since 2014 and the code is being re-written from scratch. See [here](https://github.com/orange-lang/orange/tree/inactive/rev-0) for the old code.

People who pulled `master` before January 2017 may have to do a force reset to the new master branch. 

# Resources

* [Language Guide](http://docs.orange-lang.org/v/rev-3/) ([Github](https://github.com/orange-lang/orange-docs/tree/rev-3))

# Building
Building on OS X, Linux, and Windows are supported. Make sure to install `go` and then simply run the following command:

```sh 
$ go get github.com/orange-lang/orange/...
``` 

# Community

Orange has a [Gitter](https://gitter.im/orange-lang/orange?utm_source=share-link&utm_medium=link&utm_campaign=share-link). Come say hi! Feel free to open any issues on Github about questions, suggestions, or bugs. We also have a [Google Group](https://groups.google.com/forum/#!forum/orange-lang) open to the public.
