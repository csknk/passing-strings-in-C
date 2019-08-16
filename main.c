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
	// ----------------------------------
	char *s = malloc(BUFFER_SIZE + 1);

	amend(strP, BUFFER_SIZE);
	amend(s, BUFFER_SIZE);
	
	printf("Amended char array: %s\n", str);
	printf("Amended char pointer: %s\n", s);
	free(s);

	char fixed[] = "David is ";
	char *fixedPtr = fixed;
	char *sentence = NULL;
	puts("Set buffer dynamically");
	setBufferDynamically(fixedPtr, &sentence);
	printf("sentence: %s\n", sentence);
	
	// Memory for sentence was dynamically allocated in setBufferDynamically()
	// ----------------------------------------------------------------------- 
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


// Get string from user and concatenate it onto src.
// We don't know the final length of the string.
// Write the concatenated strings into resultBuffer.
int setBufferDynamically(const char *src, char **resultBuffer)
{
	// Initalise the variables required by getline()
	// ---------------------------------------------
	char *userStr = NULL;	// To be dynamically allocated by getline()
	size_t len = 0;		// Length allocated by getline()
	ssize_t lineSize = 0;	// Length of chars read by getline

	// Get line with getlline()
	// ------------------------
	puts("Enter a line to be read by getline():");
	lineSize = getline(&userStr, &len, stdin);

	// Replace the terminating newline with a NUL - wastes a byte
	// -----------------------------------------------------------
	userStr[strcspn(userStr, "\n")] = 0;

	// Compute the size for the new string
	// -----------------------------------
	size_t totalSize = strlen(src) + lineSize + 1;

	// Allocate memory for the result buffer to account for the concatenation
	// ----------------------------------------------------------------------
	*resultBuffer = calloc(totalSize + 1, sizeof **resultBuffer);
	
	// Copy src into resultBuffer - you can't strcat() into an empty buffer
	// --------------------------------------------------------------------
	strcpy(*resultBuffer, src);

	// Concatenate userStr onto resultBuffer
	// -------------------------------------
	strcat(*resultBuffer, userStr);

	// Release memory dynamically allocated by getline()
	// -------------------------------------------------
	free(userStr);

	return (int)totalSize;
}
