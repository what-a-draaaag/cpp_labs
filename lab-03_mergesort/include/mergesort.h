#ifndef MERGESORT.H
#define MERGESORT.H

#include <stddef.h>

void mergesort(
    void* array,
    size_t elements, size_t element_size,
    int* (comparator)(const void*, const void*)
);

#endif