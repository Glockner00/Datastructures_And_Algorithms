// VisualizeHeap.c
#include "minHeap.h"
#include <ncurses.h>



 void printHeap(MinHeap* heap) {
    // inorder traversal of the tree
    printw("Min Heap:\n");
    for (int i=0; i<heap->size; i++) {
        printw("%d -> ", heap->array[i].value);
    }
    printw("\n-----------------");
    refresh();
} 


int main() {
  initscr();            // Initialize ncurses
  noecho();             // Don't echo keypresses
  cbreak();             // Disable line buffering
  keypad(stdscr, TRUE); // Enable special key handling
  MinHeap *heap = createMinHeap(10);
  int ch;
  do {
    printHeap(heap);
    printw("\ni : insert value\n");
    printw("e : extract value\n");
    printw("-----------------\n");
    printw("Enter operator: ");
    refresh();
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
    case 'e':
      break;
    }
  } while (ch != 'q');
  endwin();
  destroyMinHeap(heap);
  return 0;
}
