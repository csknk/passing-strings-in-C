#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10

void amend(char *str, size_t len);
int setBufferDynamically(const char *src, char **resultBuffer);

int main()
{
	char str[BUFFER_SIZE + 1] = "";	// Initialise empty char array
	char *strP = str;		// Pointer to the first element of str

	// Empty char pointer, heap allocated
	char *s = malloc(BUFFER_SIZE + 1);

	amend(strP, BUFFER_SIZE);
	amend(s, BUFFER_SIZE);
	
	printf("Amended char array: %s\n", str);
	printf("Amended char pointer: %s\n", s);
	free(s);

	char fixed[] = "David is ";
	char *fixedPtr = fixed;
	char *sentence = NULL;
	setBufferDynamically(fixedPtr, &sentence);
	printf("sentence: %s\n", sentence);
	free(sentence);
	return 0;
}

void amend(char *str, size_t len)
{
	for(size_t i = 0; i < len; i++) {
		*(str + i) = 'x';
	}
	// Add a NUL terminator to complete the string
	*(str + len) = 0;
}

// Don't know the final length of the string - maybe it's determined by
// user input or similar.
int setBufferDynamically(const char *src, char **resultBuffer)
{

	for (size_t i = 0; i < strlen(src); i++) {
		printf("src[%lu] = %c\n", i, src[i]);
	}

	char *userStr = NULL; // This will be dynamically allocated by getline()
	size_t len = 0;
	ssize_t lineSize = 0;
	lineSize = getline(&userStr, &len, stdin);
	userStr[strcspn(userStr, "\n")] = 0;
	size_t totalSize = strlen(src) + lineSize + 1;
	*resultBuffer = realloc(*resultBuffer, totalSize + 1);
	memset(*resultBuffer, 'a', totalSize);
	strcpy(*resultBuffer, src);	// strcpy first - can't strcat into an empty buffer
	strcat(*resultBuffer, userStr);
	free(userStr);
	return (int)totalSize;
}
