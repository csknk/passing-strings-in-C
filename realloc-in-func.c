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


