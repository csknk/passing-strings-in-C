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
	*(*s + length + 2) = 0;
}

/**
 * As `add_xy()` but with better handling for realloc errors.
 **/
void add_ab(char **s, size_t length)
{
	// The realloc returns NULL if the request for additional memory failed.
	// As such, do not assign the return value of a realloc call to the 
	// original pointer - realloc failure results in this being set NULL.
	// Use a temporary pointer instead of the same type instead, and assign
	// this memory block to the original pointer only if the realloc() call
	// is successful. 
	char *tmp = realloc(*s, length + 3);
	if (tmp == NULL) {
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	*s = tmp;
	*s = realloc(*s, length + 3);
	*(*s + length) = 'a';
	*(*s + length + 1) = 'b';
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
	add_ab(&s, strlen(s));
	printf("%s\n", s);

	// getline() allocated memory, add_xy() reallocated. Free it.
	free(s);
}


