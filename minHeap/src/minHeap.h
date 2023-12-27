// minHeap.h
#ifndef MIN_HEAP_H
#define MIN_HEAP_H

typedef struct {
  int value;
} HeapNode;

typedef struct {
  HeapNode *array;
  int size;
  int maxSize;
} MinHeap;

// function declaration
MinHeap *initMinHeap();
MinHeap *insertMinHeap(MinHeap *heap, HeapNode newNode);
MinHeap *destroyMinHeap(MinHeap *heap);
MinHeap *heapify(MinHeap *heap, int index);
MinHeap *deleteMin(MinHeap *heap);
MinHeap *deleteNode(MinHeap *heap, int targetValue);
MinHeap *reallocateMemory(MinHeap *heap);
HeapNode getMinNode(MinHeap *heap);
int findValueIndex(MinHeap *heap, int targetValue, int currIndex);
int getParentIndex(int i);
int getLeftChildIndex(int i);
int getRightChildIndex(int i);
int calculateHeapHeight(MinHeap *heap);
#endif
