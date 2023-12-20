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
MinHeap *createMinHeap(int maxSize);
MinHeap *insertMinHeap(MinHeap *heap, HeapNode newNode);
MinHeap *destroyMinHeap(MinHeap *heap);
MinHeap *heapify(MinHeap *heap, int index);
int getParentIndex(int i);
int getLetfChildIndex(int i);
int getRightChildIndex(int i);
int getMinValue(MinHeap *heap);
#endif
