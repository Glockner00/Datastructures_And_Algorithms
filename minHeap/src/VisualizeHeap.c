#include "minHeap.h"
#include <ncurses.h>

void printHeap(MinHeap *heap)
{


}

int main()
{
    initscr(); // Initialize ncurses
    noecho();  // Don't echo keypresses
    cbreak();  // Disable line buffering
    keypad(stdscr, TRUE); // Enable special key handling    
    MinHeap *heap = createMinHeap(15);


    return 0; 


}
