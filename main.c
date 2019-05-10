#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

void amend(char **str, size_t len);

int main()
{
	// Empty char array
	char str[BUFFER_SIZE + 1] = "";	// Initialises a char array of (BUFFER_SIZE + 1) NUL elements
	char *strP = str;		// Pointer to the first element of str

	// Empty char pointer, heap allocated
	char *s = malloc(BUFFER_SIZE + 1);

	amend(&strP, BUFFER_SIZE);
	amend(&s, BUFFER_SIZE);
	
	printf("Amended char array: %s\n", str);
	printf("Amended char ponter: %s\n", s);
	free(s);
	return 0;
}

void amend(char **str, size_t len)
{
	for(size_t i = 0; i < len; i++) {
		printf("i: %lu\n", i);
		*(*str + i) = 'x';
	}
	*(*str + len) = 0;
}
