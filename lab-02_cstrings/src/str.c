#include <stddef.h>

char* my_strcpy(char* destination, char* source)
{
	char* result = destination;
	while (*source)
	{
		*destination = *source;
		source++;
		destination++;
	}
	*(destination) = '\0';
	return result;
}

size_t my_strlen(char* str)
{
	size_t length = 0;
	while (*str)
	{
		str++;
		length++;
	}
	return length;
}

char* my_strcat(char* destination, char* source)
{
	char* result = destination;
	while (*destination)
	{
		destination++;
	}
	while (*source)
	{
		*destination = *source;
		source++;
		destination++;
	}
	*(destination) = '\0';
	return result;
}

int my_strcmp(char* string1, char* string2)
{
	while(*string1 == *string2 && *string1 && *string2)
	{
		string1++;
		string2++;
	}
	return (*string1 - *string2);
}