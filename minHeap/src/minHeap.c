#include "minHeap.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

// Function to reallocate memory for the heap based on its current state
MinHeap *reallocateMemory(MinHeap *heap) {
  int currentHeight = calculateHeapHeight(heap);
  int newLowerMax =
      (pow(2, (currentHeight + 1)) - 1); // 2^(currentHeight + 1) - 1

  // Check if the heap is empty; if so, allocate memory for one element
  if (heap->size == 0) {
    heap->array = realloc(heap->array, sizeof(HeapNode));
    return heap;
    // If maxSize is too small, double the memory for another level
  } else if (heap->size >= heap->maxSize) {
    int newMaxSize = (pow(2, currentHeight + 2) -
                      1); // 2^(currentHeight + 2) - 1 (starting at zero)
    heap->array = realloc(heap->array, newMaxSize * sizeof(HeapNode));
    heap->maxSize = newMaxSize;
    return heap;
    // If too much memory is allocated, take away half (a level's worth)
  } else if (heap->size == newLowerMax) {
    heap->array = realloc(heap->array, newLowerMax * sizeof(HeapNode));
    heap->maxSize = newLowerMax;
    return heap;
  } else {
    // No need for changing the memory.
    return heap;
  }
}

// Initialize an empty min heap
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
  heap->size = 0;    // Initialize the size of the heap.
  heap->maxSize = 1; // Set the maxSize
  return heap;
}

/**
 * Insertion into the minHeap.
 *
 * We are first adding the element to the bottom of the heap, we
 * later on keep performing swaps with its parents. We keep doing this
 * until we reach a parent that is lesser than the inserted node or
 * until we reach the root node.
 *
 * Time complexity of an insertion operation: O(log(n))
 */
MinHeap *insertMinHeap(MinHeap *heap, HeapNode node) {
  if (heap->size == heap->maxSize) {
    reallocateMemory(heap);
  }

  heap->array[heap->size] = node; // Set the node at the end of the array.
  int currentIndex = heap->size;  // Current index is the last in the array.
  heap->size++;

  // Perform swaps with parents until reaching the root or a lesser parent
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
 * Heapify - rearrange the heap so it maintains its minHeap property.
 *
 * Checking if a node's children are smaller than itself. If so, swap elements
 * upwards in the tree. This is done recursively until reaching the root node.
 *
 * Time Complexity of a minHeapify operation: O(log(n))
 */
MinHeap *minHeapify(MinHeap *heap, int currIndex) {
  // No swaps needed if the heap has one element or is empty
  if (heap->size <= 1) {
    return heap;
  }

  int left = getLeftChildIndex(currIndex);
  int right = getRightChildIndex(currIndex);
  int minElementIndex = currIndex; // Starting by setting the current index as
                                   // the smallest element.

  // If the left child is smaller than the current index, it is the smallest.
  if (left < heap->size &&
      heap->array[left].value < heap->array[currIndex].value) {
    minElementIndex = left;
  }
  // If the right child is smaller than the current index, it is the smallest.
  if (right < heap->size &&
      heap->array[right].value < heap->array[minElementIndex].value) {
    minElementIndex = right;
  }
  // If the minElement's index differs from the currentIndex, swap elements.
  if (minElementIndex != currIndex) {
    HeapNode tempNode = heap->array[currIndex];
    heap->array[currIndex] = heap->array[minElementIndex];
    heap->array[minElementIndex] = tempNode;
    heap = minHeapify(heap, minElementIndex);
  }
  return heap;
}

/**
 * Sets the last element on top and decreases the size by one.
 * Maintain the min heap property with a minHeapify operation.
 *
 * Time complexity of deleteMin is the same as minHeapify operation:
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
  reallocateMemory(heap);
  return heap;
}

// Delete a node with a specific target value from the heap
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
    reallocateMemory(heap);
  }
  return heap;
}

/* Helper function to find the index of a target value in the heap
 * This needs to be reworked. Worst case is O(n), best case is O(1)
 * and average case is something between because we dont usally dont
 * need to search the whole tree to find our value.
 * */
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

// Deallocate memory and destroy the heap
MinHeap *destroyMinHeap(MinHeap *heap) {
  free(heap->array);
  free(heap);
  return heap;
}

// Helper function to get the parent index of a given index
int getParentIndex(int i) { return (i - 1) / 2; }

// Helper function to get the left child index of a given index
int getLeftChildIndex(int i) { return (2 * i + 1); }

// Helper function to get the right child index of a given index
int getRightChildIndex(int i) { return (i * 2 + 2); }

/**
 * We know that the smallest value always will be at the root.
 * Time complexity: O(1)
 */
HeapNode getMinNode(MinHeap *heap) { return heap->array[0]; }

/**
 * Returns the maximum height of the tree.
 */
int calculateHeapHeight(MinHeap *heap) { return (int)floor(log2(heap->size)); }
