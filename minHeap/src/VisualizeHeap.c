// VisualizeHeap.c
#include "minHeap.h"
#include <ncurses.h>

void printHeapTree(MinHeap *heap, int index, int space) {
  if (index < heap->size) {
    // Increase distance between levels
    space += 3;

    // Process right child first
    printHeapTree(heap, getRightChildIndex(index), space);

    // Print current node
    for (int i = 3; i < space; i++)
      printw(" ");
    printw("%d\n", heap->array[index].value);

    // Process left child
    printHeapTree(heap, getLeftChildIndex(index), space);
  }
}

/*  Expected output:
                 1
               /    \
             3        5
           /  \     /  \
         4      6  13  10
        / \    / \
       9   8  15 17
 */

void testInput(MinHeap *heap) {
  HeapNode newNode0 = {1};
  insertMinHeap(heap, newNode0);

  HeapNode newNode1 = {3};
  insertMinHeap(heap, newNode1);

  HeapNode newNode2 = {5};
  insertMinHeap(heap, newNode2);

  HeapNode newNode3 = {4};
  insertMinHeap(heap, newNode3);

  HeapNode newNode4 = {6};
  insertMinHeap(heap, newNode4);

  HeapNode newNode5 = {13};
  insertMinHeap(heap, newNode5);

  HeapNode newNode6 = {10};
  insertMinHeap(heap, newNode6);

  HeapNode newNode7 = {9};
  insertMinHeap(heap, newNode7);

  HeapNode newNode8 = {8};
  insertMinHeap(heap, newNode8);

  HeapNode newNode9 = {15};
  insertMinHeap(heap, newNode9);

  HeapNode newNode10 = {17};
  insertMinHeap(heap, newNode10);
}

void printHeap(MinHeap *heap) {
  clear();
  refresh();
  printHeapTree(heap, 0, 0);
  printw("-----------------\n");
  printw("i : insert value\n");
  printw("m : extract minimum\n");
  printw("d : delete element\n");
  printw("t : test input\n");
  printw("c : clear heap\n");
  printw("q : quit\n");
  printw("-----------------\n");
  printw("Enter operator: ");
  refresh();
}

int main() {
  initscr();            // Initialize ncurses
  noecho();             // Don't echo keypresses
  cbreak();             // Disable line buffering
  keypad(stdscr, TRUE); // Enable special key handling
  MinHeap *heap = createMinHeap(15);
  int ch;
  int value;

  do {
    printHeap(heap);
    ch = getch();
    switch (ch) {
    case 'i':
      printw("\nEnter value to insert: ");
      refresh();
      scanw("%d", &value);
      HeapNode newNode = {value};
      insertMinHeap(heap, newNode);
      break;
    case 'm':
      delete_minimum(heap);
      break;
    case 'd':
      printw("\nEnter the value to remove: ");
      break;
    case 't':
      testInput(heap);
      break;
    case 'c':
      destroyMinHeap(heap);
      MinHeap *heap = createMinHeap(15);
      break;
    }
  } while (ch != 'q');
  endwin();
  destroyMinHeap(heap);
  return 0;
}
