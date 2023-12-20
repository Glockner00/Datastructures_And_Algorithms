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
 * THis kinda worky
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
  while (currIndex >= 0 &&
         heap->array[parentIndex].value > heap->array[currIndex].value) {
    int temp = heap->array[parentIndex].value;
    heap->array[parentIndex] = heap->array[currIndex];
    heap->array[currIndex].value = temp;
    currIndex = parentIndex;
  }

  return heap;
}

/**
 * Heapify - rearrange the heap so it maintains it minHeap property.
 *
 * Checking if a nodes children are smaller than it self. If so is the
 * case we will start to swap elements upwords in the tree. We are doing
 * this recursivly until we reach the root node.
 *
 * Time Complexity of a heapify operation: O(log(n))
 *
 * This shit i dont now if worky
 */

MinHeap *heapify(MinHeap *heap, int currIndex) {
  // No swaps needed
  if (heap->size <= 1) {
    return heap;
  }

  int left = getLeftChildIndex(currIndex);
  int right = getRightChildIndex(currIndex);
  int minElementIndex = currIndex; // starting by setting the current index as
                                   // the smallest element.

  // if the left child is smaller than this the currentIndex, it is the
  // smallest.
  if (left < heap->size &&
      heap->array[left].value < heap->array[currIndex].value) {
    minElementIndex = left;
  }
  // if the right child is smaller than this, we now know that we are at the
  // smallest element of the subtree.
  if (right < heap->size &&
      heap->array[right].value < heap->array[minElementIndex].value) {
    minElementIndex = right;
  }
  // if the minelements index differs from the currentIndex we start swapping.
  if (minElementIndex != currIndex) {
    int temp = heap->array[minElementIndex].value;
    heap->array[currIndex] = heap->array[minElementIndex];
    heap->array[minElementIndex].value = temp;
    heap = heapify(heap, minElementIndex);
  }

  return heap;
}

/**
 * Deletes the minium element of the heap, aka the root.
 *
 *
 * This nono worky
 */

MinHeap *delete_minimum(MinHeap *heap){
    // no element to delete
    if(heap->size==0){
        return heap;
    }

    int size = heap->size;
    int lastElement = heap->array[size-1].value;
    heap->array[0].value = lastElement;
    heap->size--;
    size--;
    return heapify(heap, 0);
}

MinHeap *delete_element(MinHeap *heap, int currIndex){
    return heap;
}



MinHeap *destroyMinHeap(MinHeap *heap) {
  free(heap->array);
  free(heap);
  return heap;
}

int getParentIndex(int i) { return (i - 1) / 2; }

int getLeftChildIndex(int i) { return (2 * i + 1); }

int getRightChildIndex(int i) { return (i * 2 + 2); }

int getMinValue(MinHeap *heap) { return heap->array[0].value; }
