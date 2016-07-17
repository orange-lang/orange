# Orange Contribution Guide

Thank you for wanting to contribute to Orange! The `rev-2` branch is a complete rewrite of the language and compiler, and any help is appreciated getting it off the ground. The main areas that could use refinments right now are:

- Improving the [documentation](https://github.com/orange-lang/orange-docs/tree/rev-2) of Orange
- Improving the [language](http://docs.orange-lang.org/v/rev-2/).
- Improving existing/writing new [unit tests](https://github.com/orange-lang/orange/tree/rev-2/test).
- Making the compiler feature-complete.

## Improving the Documentation

The Orange `rev-2` documentation could use a lot of work to make language elements clear and obvious to newcomers to the language. The Orange documentation uses Gitbooks and the repository for it is on [Github](https://github.com/orange-lang/orange-docs/tree/rev-2).

## Improving the Language

Orange's `rev-2` branch is still a work in progress, and any suggestions as to how the language can change to meet the language's goals are welcome.

## Improving Existing/Writing New Unit Tests

The [unit tests](https://github.com/orange-lang/orange/tree/rev-2/test) could always use improvements to test for more intricate cases, introduce new tests for bugs that were fixed, or a combination of fixing bugs and writing new tests for that bug.

## Making the compiler feature-complete.

Since `rev-2` is still getting started, it's nowhere near feature-complete. Currently, `libanalysis` is the current focus point. Work on it entails taking an AST expression and determining the type, and reporting any errors, if appropriate.
