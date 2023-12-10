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

int str_comparator(const void *a, const void *b)
{
	return strcmp(*(const char**)a, *(const char**)b);
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
		print_array("int", array, elements);
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
		print_array("char", array, elements);
		free(array);
	}
	else if (!strcmp(type, "str"))
	{
		element_size = sizeof(char*);
		comparator = str_comparator;
		char** array = (char**)malloc(element_size * elements);
		assert(array != NULL);
		for (int i = 0; i < elements; i++)
		{
			array[i] = argv[i + 2];
		}
		mergesort(array, elements, element_size, str_comparator);
		print_array("str", array, elements);
		free(array);
	}
}

void print_array(const char* type, void* array, int elements)
{
	if (elements!=0)
	{
		for (int i = 0; i < elements; i++)
			{
				if(!strcmp(type,"int"))
				{
					int* p = (int*)array;
					printf("%d", p[i]);
				}
				else if (!strcmp(type,"char"))
				{
					char* p = (char*)array;
					printf("%c", p[i]);
				}
				else
				{
					char** p = (char**)array;
					printf("%s", p[i]);
				}
				if (i == elements - 1)
				{
					printf("\n");
				}
				else
				{
					printf(" ");
				}
			}
	}
}