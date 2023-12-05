#include"stddef.h"
#include"stdlib.h"
#include"assert.h"


void mergesort(void* array, size_t elements, 
	size_t element_size, int (comparator)(const void*, const void*))
{
	merge_sort(array, element_size, 0, elements, comparator);
}

void merge_sort(void* array, size_t element_size, int left, 
	int right, int (comparator)(const void*, const void*))
{
	if (left >= right - 1)
	{
		return;
	}
	int mid = (left + right) / 2;
	merge_sort(array, element_size, left, mid, comparator);
	merge_sort(array, element_size, mid, right, comparator);
	merge(array, element_size, left, mid, right, comparator);
}

void merge(void* array, size_t element_size, int left, int mid, int right,
	int (comparator)(const void*, const void*))
{
	char* a = malloc((right - left) * element_size);
	assert(a != NULL);
	int iter1 = left;
	int iter2 = mid;
	char* p = array;
	int i = 0;
	while(iter1 < mid || iter2 < right)
	{
		if ((iter1 < mid && comparator(p + iter1 * element_size, p + iter2 * element_size) <= 0) || iter2 >= right)
		{
			copy(p + iter1 * element_size, a + i * element_size, element_size);
			iter1++;
			i++;
			
		}
		else
		{
			copy(p + iter2 * element_size, a + i * element_size, element_size);
			iter2++;
			i++;
		}
	}
	for (int j = 0; j < right - left; j++)
	{
		copy(a + j * element_size, p + left * element_size + j * element_size, element_size);
	}
	free(a);
}

void copy(void* source, void* destination, size_t element_size)
{
	char* elem1 = source;
	char* elem2 = destination;
	for (int i = 0; i < element_size; i++)
	{
		*elem2 = *elem1;
		elem1++;
		elem2++;
	}
}