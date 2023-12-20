// minHeap.c
#include "minHeap.h"
#include <stdlib.h>

MinHeap *createMinHeap(int maxSize) {
  MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
  if (!heap) {
    // handle memory allocation faliure
    exit(EXIT_FAILURE);
  }

  heap->array = (HeapNode *)malloc(maxSize * sizeof(HeapNode));
  if (!heap->array) {
    // handle memory allocation faliure
    free(heap);
    exit(EXIT_FAILURE);
  }
  heap->size = 0;          // initialize the size of the heap.
  heap->maxSize = maxSize; // set the maxSize
  return heap;
}

MinHeap *insertMinHeap(MinHeap *heap, HeapNode node) {
  if (heap->size == heap->maxSize) {
    // handle a full heap
    return NULL;
  }
  // Add a new node to the top of the heap and increase the size of the heap.
  int index = heap->size; // current index
  heap->array[index] = node;
  heap->size++;
  // Maintain the minHeap property with a bubble up operation.
  while (index > 0) {
    int parentIndex = (index - 1) / 2;
    if (heap->array[index].value < heap->array[parentIndex].value) {
      // Swap if parent has a greater value
      HeapNode temp = heap->array[index];
      heap->array[index] = heap->array[parentIndex];
      heap->array[parentIndex] = temp;
      index = parentIndex; // move up to the parent index.
    } else {
      break;
    }
  }
  return heap;
}

MinHeap *destroyMinHeap(MinHeap *heap) {
  free(heap->array);
  free(heap);
  return heap;
}

MinHeap *heapify(MinHeap *heap, int index){
    return heap;
}


int parentIndex(int i){
    return(i-1)/2;
}

int leftChildIndex(int i){
    return (2*i+1);
}

int rightChildIndex(int i){
    return(i*2+2);
}
int getMinValue(MinHeap *heap){
    return heap->array[0].value;
}



