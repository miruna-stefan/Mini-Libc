// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

#define NUM_MAX 100000

char *strcpy(char *destination, const char *source)
{
	// copy character by character until the end of the source is reached
	int i = 0;
	while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }

	// add the terminating null character at the end of the destination
    destination[i] = '\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	int exceeded_length = 0;

	for (size_t i = 0; i < len; i++) {
		// check if len > source's number of characters
		if (source[i] == '\0')
			exceeded_length = 1;

		/* if len exceeds the length of the source, the destination
		must be filled with terminating null characters until
		a number of len characters have been written */
		if (exceeded_length == 1)
			destination[i] = '\0';
		else
			destination[i] = source[i];
	}

	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* find the end of the destination, by storing in i the position
	of the terminating null character of the destination */
	int i = 0;
	while (destination[i] != '\0')
		i++;

	/* go through the source using the counter j and add character by
	character to the destination string, whose counter is i */
	int j = 0;
	while (source[j] != '\0') {
		destination[i] = source[j];
		j++;
		i++;
	}

	// add the terminating null character at the end of the destination
	destination[i] = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* find the end of the destination, by storing in i the position
	of the terminating null character of the destination */
	size_t i = 0;
	while (destination[i] != '\0')
		i++;

	size_t j;
	for (j = 0; j < len; j++) {
		// check if the end of the source string has been reached
		if (source[j] == '\0')
			break;

		/* if there are still characters in the string,
		copy the current character */
		destination[i] = source[j];
		i++;
	}

	// add the null terminator at the end of the destination
	destination[i] = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	int i = 0;

	/* find the first position on which the character in
	str1 is different from the character in str2 */
	while (str1[i] == str2[i]) {
		// check if the 2 strings have ended at the same time
		if (str1[i] == '\0' && str2[i] == '\0')
			return 0;
		i++;
	}

	return str1[i] - str2[i];
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		if (str1[i] != str2[i])
			return str1[i] - str2[i];

		// check if both strings have ended
		if (str1[i] == '\0' && str2[i] == '\0')
			return 0;
	}

	// if we are here, it means that the first len characters were all the same
	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == (char)c)
			return (char *)(str + i);
		i++;
	}

	/* check if the character that we are looking
	for is actually the null terminating character */
	if ((char)c == '\0')
		return (char *)(str + i + 1);

	// if we are here, it means that c was not found
	return NULL;
}

char *strrchr(const char *str, int c)
{
	int i = 0;
	int last_position = -1;

	while (str[i] != '\0') {
		if (str[i] == (char)c)
			last_position = i;
		i++;
	}

	/* check if the character that we are looking
	for is actually the null terminating character */
	if ((char)c == '\0')
		return (char *)(str + i + 1);

	// check if c was found in the string
	if (last_position == -1)
		return NULL;

	return (char *)(str + last_position);
}

char *strstr(const char *haystack, const char *needle)
{
	if (*needle == '\0')
		return (char *)haystack;

	int i = 0;
	int restore_i; // copy of i
	int j;
	int found; // indicates whether the needle was found in the haystack

	while (haystack[i] != '\0') {
		/* compare each character in haystack with
		the first character of needle. */
		if (haystack[i] == needle[0]) {
			restore_i = i;
			found = 1;

			/* see if the rest of the characters
			in needle match the next characters in haystack */
			j = 1;
			i++;
			while (needle[j] != '\0' && found == 1) {
				if (haystack[i] != needle[j]) {
					i = restore_i;
					found = 0;
				}
				if (haystack[i] == '\0')
					found = 0;
				i++;
				j++;
			}

			// check if a match was found
			if (found == 1)
				return (char *)(haystack + restore_i);
		}
		i++;
	}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* store result in res, namely pointer to
	the last occurance of needle in haystack */
	char *res;

	/* variable that indicates whether the needle
	string has been found in haystack */
	int found = 0;

	char *aux;
	aux = strstr(haystack, needle);

	// call strstr until we reach the last occurance of the needle string
	while (aux != NULL) {
		// update found when finding the needle in the haystack
		if (found == 0)
			found = 1;

		res = aux;
		haystack = res + 1;

		aux = strstr(haystack, needle);
	}

	// check whether needle exists in haystack (at least once)
	if (found == 0)
		return NULL;

	return res;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	for (size_t i = 0; i < num; i++) {
		// check if we haven't reached the end of the word
		if (*(const char *)(source + i) == '\0')
			break;

		*(char *)(destination + i) = *(const char *)(source + i);
	}
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* to handle overlap, we need to use an auxiliary string when
	moving the characters from source to destination */
	char aux[NUM_MAX];

	// copy the source string in aux
	for (size_t i = 0; i < num; i++)
		aux[i] = *(const char *)(source + i);

	//copy aux in destination
	for (size_t i = 0; i < num; i++)
		*(char *)(destination + i) = aux[i];

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t i; // counter

	for (i = 0; i < num; i++) {
		if (*(const char *)(ptr1 + i) != *(const char *)(ptr2 + i)) {
			// found a different character
			return *(const char *)(ptr1 + i) - *(const char *)(ptr2 + i);
		}
	}

	// if we reached this point, the compared strings were identical
	return 0;
}

void *memset(void *source, int value, size_t num)
{
	// set each position of the string to the given value
	for (size_t i = 0; i < num; i++)
		*(char *)(source + i) = (char)value;

	return source;
}
