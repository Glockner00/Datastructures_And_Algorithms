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
  if (heap->size == heap->maxSize) {
    fprintf(stderr, "Cannot insert %d, heap is full.\n", node.value);
    return heap;
  }

  heap->array[heap->size] = node; // set the node at the end of the array.
  int currentIndex = heap->size;  // current index is the last in the array.
  heap->size++;

  while (currentIndex > 0 && heap->array[getParentIndex(currentIndex)].value >
                                 heap->array[currentIndex].value) {
    HeapNode tempNode = {heap->array[getParentIndex(currentIndex)].value};
    heap->array[getParentIndex(currentIndex)] = heap->array[currentIndex];
    heap->array[currentIndex] = tempNode;
    currentIndex = getParentIndex(currentIndex);
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
    HeapNode tempNode = heap->array[minElementIndex];
    heap->array[currIndex] = heap->array[minElementIndex];
    heap->array[minElementIndex] = tempNode;
    //heap = heapify(heap, minElementIndex);
  }

  return heap;
}

/**
 * Deletes the minium element of the heap, aka the root.
 *
 *
 * This nono worky
 */

MinHeap *delete_minimum(MinHeap *heap) {
  if (!heap || heap->size == 0) {
    return heap;
  }
  int size = heap->size;
  HeapNode lastNode = heap->array[size - 1];
  heap->array[0] = lastNode;
  heap->size--;
  size--;
  heap = heapify(heap,0);
  return heap;
}

MinHeap *delete_element(MinHeap *heap, int currIndex) { return heap; }

MinHeap *destroyMinHeap(MinHeap *heap) {
  free(heap->array);
  free(heap);
  return heap;
}

int getParentIndex(int i) { return (i - 1) / 2; }

int getLeftChildIndex(int i) { return (2 * i + 1); }

int getRightChildIndex(int i) { return (i * 2 + 2); }

int getMinValue(MinHeap *heap) { return heap->array[0].value; }
