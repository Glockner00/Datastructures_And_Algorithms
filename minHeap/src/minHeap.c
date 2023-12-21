// minHeap.c
#include "minHeap.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


// TODO: what if the heap is empty?
// TODO: Can we use the same function for decreasing the size?
MinHeap *reallocateMemory(MinHeap *heap) {
  int currentHeight = calculateHeapHeight(heap);
  // If the current height is not sufficient, reallocate memory
  int newMaxSize = (pow(2, currentHeight + 2) -
                    1); // 2^(currentHeight + 2) - 1 (we start at zero)
  heap->array = realloc(heap->array, newMaxSize * sizeof(HeapNode));
  heap->maxSize = newMaxSize;
  return heap;
}

MinHeap *initMinHeap() {
  MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
  if (!heap) {
    fprintf(stderr, "Failed to allocate memory for the heap.");
    exit(EXIT_FAILURE);
  }

  heap->array = (HeapNode *)malloc(sizeof(HeapNode));
  if (!heap->array) {
    fprintf(stderr, "Failed to allocate memory for the heap.");
    free(heap);
    exit(EXIT_FAILURE);
  }
  heap->size = 0;    // initialize the size of the heap.
  heap->maxSize = 1; // set the maxSize
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
    reallocateMemory(heap);
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
 * Time Complexity of a minHeapify operation: O(log(n))
 *
 */

MinHeap *minHeapify(MinHeap *heap, int currIndex) {
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
  // if the minelement's index differs from the currentIndex we start swapping.
  if (minElementIndex != currIndex) {
    HeapNode tempNode = heap->array[currIndex];
    heap->array[currIndex] = heap->array[minElementIndex];
    heap->array[minElementIndex] = tempNode;
    heap = minHeapify(heap, minElementIndex);
  }
  return heap;
}

/**
 * Sets the last element on top and decreesas the size by one.
 * Maintain the min heap property with a minHeapify operation.
 *
 * Time complexity of deleteMin is the same a minHeapify operartion:
 * O(log(n))
 */

MinHeap *deleteMin(MinHeap *heap) {
  if (heap->size == 0) {
    return heap;
  }
  HeapNode lastNode = heap->array[heap->size - 1];
  heap->array[0] = lastNode;
  heap->size--;
  heap = minHeapify(heap, 0); 
  return heap;
}

MinHeap *deleteNode(MinHeap *heap, int targetValue) {
  if (heap->size == 0) {
    // Heap is empty, nothing to delete
    return heap;
  }

  // Find the index of the target value using a helper function
  // Worst case O(n), average case is much better but not constant.
  int targetIndex = findValueIndex(heap, targetValue, 0);

  if (targetIndex != -1) {
    // Value found, perform deletion
    heap->array[targetIndex] = heap->array[heap->size - 1];
    heap->size--;
    heap = minHeapify(heap, targetIndex);
  }
  return heap;
}

int findValueIndex(MinHeap *heap, int targetValue, int currIndex) {
  if (currIndex >= heap->size) {
    // Value not found, or currIndex is out of bounds.
    return -1;
  }

  if (heap->array[currIndex].value == targetValue) {
    // Value found, return the index
    return currIndex;
  } else if (heap->array[currIndex].value > targetValue) {
    // If the current node's value is greater, stop searching in this subtree.
    return -1;
  } else {
    // Recursively search in the left and right subtrees
    int leftIndex =
        findValueIndex(heap, targetValue, getLeftChildIndex(currIndex));
    if (leftIndex != -1) {
      return leftIndex; // Value found in the left subtree
    }

    int rightIndex =
        findValueIndex(heap, targetValue, getRightChildIndex(currIndex));
    return rightIndex; // Value found in the right subtree (or -1 if not found)
  }
}

MinHeap *destroyMinHeap(MinHeap *heap) {
  free(heap->array);
  free(heap);
  return heap;
}

int getParentIndex(int i) { return (i - 1) / 2; }

int getLeftChildIndex(int i) { return (2 * i + 1); }

int getRightChildIndex(int i) { return (i * 2 + 2); }

/**
 * We know that the smallest value allways will be at the root.
 * Time complexity: O(1)
 */
HeapNode getMinNode(MinHeap *heap) { return heap->array[0]; }

/**
 * Returns the maximum height of the tree.
 */
int calculateHeapHeight(MinHeap *heap) { return (int)floor(log2(heap->size)); }
