#include"stdio.h"
#include"mergesort.h"
#include"stddef.h"
#include"string.h"
#include"stdlib.h"
#include"assert.h"


int int_comparator(const void* a, const void* b)
{
	return *(const int*)a - *(const int*)b;
}

int char_comparator(const void* a, const void* b)
{
	return *(const char*)a - *(const char*)b;
}

int str_comparator(const void* a, const void* b)
{
	return strcmp(*(const char**) a, *(const char**) b);
}


int main(int argc, void** argv)
{
	size_t element_size;
	size_t elements = argc - 2;
	int (*comparator)(void*, void*);
	const char* type = argv[1];

	if (!strcmp(type, "int"))
	{
		element_size = sizeof(int);
		comparator = int_comparator;
		int* array = (int*)malloc(element_size * elements);
		assert(array != NULL);
		for (int i = 0; i < elements; i++)
		{
			array[i] = atoi(argv[i + 2]);
		}
		mergesort(array, elements, element_size, int_comparator);
		for (int i = 0; i < elements; i++)
		{
			printf("%d", array[i]);
			if (i == elements - 1)
			{
				printf("\n");
			}
			else
			{
				printf(" ");
			}
		}
		free(array);
	}
	else if (!strcmp(type, "char"))
	{
		element_size = sizeof(char);
		comparator = char_comparator;
		char* array = (char*)malloc(element_size * elements);
		assert(array != NULL);
		for (int i = 0; i < elements; i++)
		{
			array[i] = *((char*)argv[i + 2]);
		}
		mergesort(array, elements, element_size, char_comparator);
		for (int i = 0; i < elements; i++)
		{
			printf("%c", (char*)array[i]);
			if (i == elements - 1)
			{
				printf("\n");
			}
			else
			{
				printf(" ");
			}
		}
		free(array);
	}
	else if (!strcmp(type, "str"))
	{
		element_size = sizeof(argv[2]);
		comparator = str_comparator;
		char** array = (char**)malloc(element_size * elements);
		assert(array != NULL);
		for (int i = 0; i < elements; i++)
		{
			array[i] = argv[i + 2];
		}
		mergesort(array, elements, element_size, str_comparator);
		for (int i = 0; i < elements; i++)
		{
			printf("%s", array[i]);
			if (i == elements - 1)
			{
				printf("\n");
			}
			else
			{
				printf(" ");
			}
		}
		free(array);
	}
}