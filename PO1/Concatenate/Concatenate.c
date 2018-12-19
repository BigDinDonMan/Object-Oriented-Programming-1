#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define null NULL


char* concatenate(const char *first, const char *second) {
	if (!first || !second) return null;
	int len1 = strlen(first), len2 = strlen(second);
	char* result = (char*)calloc(len1 + len2 + 2, sizeof(char));
	if (!result) return null;
	int i = 0, j = 0;
	for (; i < len1; ++i) {
		result[i] = first[i];
	}
	result[i++] = ' ';
	for (;j < len2; ++j, ++i) {
		result[i] = second[j];
	}
	return result;
}




int main(void) {
	
	char* first = "Ala", *second = "ma kota";
	printf("Before: %s\n%s\n", first, second);
	char *result = concatenate(first, second);
	if (result) {
		printf("After: %s\n", result);
		free(result);
	}
	return 0;
}