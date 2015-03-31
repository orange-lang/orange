# Orange Tests

The tests in each subdirectory have been arranged to have the following precedence, from highest to lowest:

```
basic/
functions/
if/
variables/
loops/
array/
morphing/
pointers/
programs/
bugs/
``` 

That is to say, tests in `array/` depend on tests in `loops/` and `if/` passing, as `array/` has a lower precedence. 
