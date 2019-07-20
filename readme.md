Strings in C: Access String in Function
=======================================
If you need to operate on strings, it's helpful to abstract this away into separate functions (which can be held in different files) to keep your code clean and to reduce repetition.

In C, parameters are always passed by value. In order to change a string variable, function parameters should include:

* A pointer to a pointer to the first char in the string
* The length of the string (though this can be determined within the function).

Passing in a pointer to a char pointer means that the function receives a memory address (i.e. pointer) which holds the memory address of the first char in the string.

Amend Stack-Allocated String in a Function
------------------------------------------
In C, if you need to amend a string in a called function, pass a pointer to the first char in the string as an argument to the function.

It is also common to pass in the length of the string:

```c
void function(char *myString, size_t lengthMyString);
```
If you don't pass the length, you can get this value from within your function by counting up to a `NUL` char - which you can do easily with `strlen()` from the `<string.h>` header:

```c
void function(char *myString)
{
  for (size_t i = 0; i < strlen(myString); i++) {
    // Access each char in the string
    printf("myString[%lu] = %c\n", i, myString[i]);
  }
}
```
If you have allocated storage for the string outside the function, which you cannot exceed within the function, it's probably a good idea to pass in the size.

Function Does Not Alter the String
----------------------------------
If you're not modifying the string, you can pass a `const` pointer and omit the length:

```c
void printString(const char *myString);
```

Amend a Passed-in Buffer With Memory Allocation
-----------------------------------------------
If the function needs to modify a dynamically allocated (i.e. heap-allocated) string buffer from the caller, you must pass in a pointer to a pointer.

In C, function arguments are passed by value. This means that to modify a variable from within a function, you need a __pointer__ to the variable.

This allows you to derefence the pointer, and potentially amend the value in the memory address being pointed to.

When you dynamically allocate memory to store a string (using one of the `malloc()` family of functions) you are assigning an area of heap memory to a `char *`.

If you need to change what is pointed to from with the function (e.g you might need to `realloc()` memory) the function must receive a pointer to the `char *`. In this way, you can dereference the `char **` to change the value held in `char *` - which in this case is the memory address of the dynamically allocated storage.

```
// char **s          char *s        char
// +---+             +---+          +---+---+---+---+
// | &-|------------>| &-|--------->|'a'|'b'|'c'| 0 |
// +---+             +---+          +---+---+---+---+
```


```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Within function, amending *s changes the memory
 * address of the dynamically allocated string.
 **/
void add_xy(char **s, size_t length)
{
	*s = realloc(*s, length + 3);
	*(*s + length) = 'x';
	*(*s + length + 1) = 'y';
	// Add a null terminator
	*(*s + length + 2) = 0;
}

int main(void)
{
	char *s = NULL;
	size_t length = 0;

	// The size of s is unknown at compile time.
	getline(&s, &length, stdin);

	// Remove newline - maybe realloc memory after this.
	s[strcspn(s, "\n")] = 0;

	add_xy(&s, strlen(s));

	printf("%s\n", s);

	// getline() allocated memory, add_xy() reallocated. Free it.
	free(s);
}


```


References
----------
* [SO Answer][1]

[1]: https://stackoverflow.com/a/1863138/3590673
