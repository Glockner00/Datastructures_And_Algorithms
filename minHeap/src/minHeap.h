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

#endif
