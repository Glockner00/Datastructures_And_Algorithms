// minHeap.c
#include "minHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

MinHeap *createMinHeap(int maxSize) {
  MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
  if (!heap) {
    fprintf(stderr, "Failed to allocate memory for the heap.");
    exit(EXIT_FAILURE);
  }

  heap->array = (HeapNode *)malloc(maxSize * sizeof(HeapNode));
  if (!heap->array) {
    fprintf(stderr, "Failed to allocate memory for the heap.");
    free(heap);
    exit(EXIT_FAILURE);
  }
  heap->size = 0;          // initialize the size of the heap.
  heap->maxSize = maxSize; // set the maxSize
  return heap;
}

/**
 * Insertion into the minHeap.
 *
 * We are first adding the element to the bottom of the heap, we
 * later on keep performing swaps with it's parents. We keep doing this
 * until we reach a parent that is lesser than the inserted node or
 * until we reach the root node.
 *
 * Time complexity of an insertion operation: O(log(n))
 *
 */
MinHeap *insertMinHeap(MinHeap *heap, HeapNode node) {
  // heap is full
  if (heap->size == heap->maxSize) {
    fprintf(stderr, "Cannot insert %d, heap is full.\n", node.value);
    return heap;
  }

  int currIndex = heap->size;
  heap->array[currIndex] = node;
  heap->size++;
  int parentIndex = getParentIndex(currIndex);

  // Maintain the minHeap property with a bubble up operation that is using
  // swaps.
  while (currIndex > 0 &&
         heap->array[parentIndex].value > heap->array[currIndex].value) {
    int temp = heap->array[parentIndex].value;
    heap->array[parentIndex] = heap->array[currIndex];
    heap->array[currIndex].value = temp;
    currIndex = parentIndex;
  }
  return heap;
}

MinHeap *destroyMinHeap(MinHeap *heap) {
  free(heap->array);
  free(heap);
  return heap;
}

MinHeap *heapify(MinHeap *heap, int currIndex) { return heap; }

int getParentIndex(int i) { return (i - 1) / 2; }

int getLeftChildIndex(int i) { return (2 * i + 1); }

int getRightChildIndex(int i) { return (i * 2 + 2); }

int getMinValue(MinHeap *heap) { return heap->array[0].value; }
