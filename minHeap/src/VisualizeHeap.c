//VisualizeHeap.c
#include "minHeap.h"
#include <ncurses.h>

void printHeap(MinHeap *heap)
{
    clear();
    //print heap array
    for(int i=0; i<heap->size; ++i){
        mvprintw(2, i*4, "%d", heap->array[i].value);
    }

    //print heap structure lines
    for(int i=0; i<=heap->size/2 ; ++i){
        int x = i*4-2;
        int y = 4;
        mvprintw(y,x,"/");
        if(2*i<heap->size){
            mvprintw(y+1,x-1,"/");
        }
        if(2*i+1<heap->size){
            mvprintw(y+1,x+1, "\\");
        }
    }
    refresh();
}

int main()
{
    initscr(); // Initialize ncurses
    noecho();  // Don't echo keypresses
    cbreak();  // Disable line buffering
    keypad(stdscr, TRUE); // Enable special key handling    
    MinHeap *heap = createMinHeap(15);
    printHeap(heap);

    return 0; 


}
