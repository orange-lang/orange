# lib/test

This folder contains a lightweight unit testing library.

# Creating tests

A test can be created in the `unit/` folder. Create a C++ source file
and include `START_TEST_MODULE();` somewhere before you define your tests.

Next, use `ADD_TEST(functionName, description)` to define a test. Afterwards,
define the function, returning an int and taking no arguments, filling it with
the contents of your test.

Tests return `1` on fail or `0` on success. Alternatively, include
`<cmd/Comparisons.h>` to use `fail()` and `pass()` respectively.

After all your tests are defined, use the macro `RUN_TESTS();`. Do _not_
define a main function, as the macro does it for you. 
