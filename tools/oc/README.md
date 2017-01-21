# oc

`oc` is the front-end binary to all of the libraries (analysis, ast, generate, etc). It's used to bootstrap the language and compile orange files into a project.

It can only produce binaries for the architecture it is being built on, and it only links against libc. It can be invoked with:

```
$ oc [ -o <output name>  ] [ -m <main file> ] <list of .or files>
```

`oc` assumes the first file in the list of files is the "main" file. If this does not the case, you can specify the main file with the `-m` switch.
