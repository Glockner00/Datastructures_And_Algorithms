#include "minHeap.h"
#include <ncurses.h>

void printHeapTree(MinHeap *heap, int index, int space) {
  if (index < heap->size) {
    // Increase distance between levels
    space += 5;

    // Process right child first
    printHeapTree(heap, getRightChildIndex(index), space);

    // Print current node
    for (int i = 5; i < space; i++)
      printw(" ");
    printw("%d\n", heap->array[index].value);

    // Process left child
    printHeapTree(heap, getLeftChildIndex(index), space);
  }
}

void printInfo(MinHeap *heap) {
  printw("\n--------------HEAP INFO----------------");
  printw("\nArray: ");
  for (int i = 0; i < heap->size; ++i) {
    printw("%d", heap->array[i].value);
    printw(" ");
  }
  printw("\n");
  printw("Heap maximum height: %d\n", calculateHeapHeight(heap));
  printw("Number of nodes allocated memory for: %d\n", heap->maxSize);
  printw("Size of array: %d\n", heap->size);
}

void printHeap(MinHeap *heap) {
  clear();
  refresh();
  printw("----------------HEAP-------------------\n");
  printHeapTree(heap, 0, 0);
  printInfo(heap);
  refresh();

  printw("---------------------------------------\n");
  printw("i : insert value\n");
  printw("m : delete minimum\n");
  printw("d : delete element\n");
  printw("c : clear heap\n");
  printw("q : quit\n");
  printw("---------------------------------------");
  printw("\nOrder in array: ");
  printw("Enter operator: ");
  refresh();
}

int main() {
  initscr();            // Initialize ncurses
  noecho();             // Don't echo keypresses
  cbreak();             // Disable line buffering
  keypad(stdscr, TRUE); // Enable special key handling
  MinHeap *heap = initMinHeap();
  int ch;

  do {
    printHeap(heap);
    ch = getch();
    switch (ch) {
    case 'i':
      printw("\nEnter value to insert: ");
      refresh();
      int value;
      scanw("%d", &value);
      HeapNode newNode = {value};
      insertMinHeap(heap, newNode);
      break;
    case 'm':
      deleteMin(heap);
      break;
    case 'd':
      printw("\nEnter the node to remove: ");
      int target;
      scanw("%d", &target);
      deleteNode(heap, target);
      break;
    case 'c':
      destroyMinHeap(heap);
      MinHeap *heap = initMinHeap();
      break;
    }
  } while (ch != 'q');
  endwin();
  destroyMinHeap(heap);
  return 0;
}
