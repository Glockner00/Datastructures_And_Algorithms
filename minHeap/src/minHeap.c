//minHeap.c
#include "minHeap.h"
#include <stdlib.h>

MinHeap *createMinHeap(int maxSize)
{
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if(!heap)
    {
        //handle memory allocation faliure
        exit(EXIT_FAILURE);
    }

    heap->array = (HeapNode*)malloc(maxSize * sizeof(HeapNode));
    if(!heap->array)
    {
        //handle memory allocation faliure
        free(heap);
        exit(EXIT_FAILURE);

    }
    heap->size = 0; // initialize the size of the heap.
    heap->maxSize = maxSize; // set the maxSize
    return heap;
}
