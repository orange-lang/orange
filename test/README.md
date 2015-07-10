# Orange Tests

When running `orange test`, Orange will test programs and projects in the `test/` subdirectory of the Orange project you're currently in. 

When running tests, any non-zero value a program returns is considered a fail. 

# Test Precedence 

The tests in each subdirectory have been arranged to have the following precedence, from highest to lowest:

```
basic/
functions/
recursion/
if/
variables/
loops/
array/
morphing/
pointers/
ternary/
enum/
sizeof/
programs/
bugs/
``` 

That is to say, tests in `array/` depend on tests in `loops/` and `if/` passing, as `array/` has a lower precedence. 
