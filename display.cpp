#include<ege.h>
#include <cstdlib> // °üº¬rand()ºÍsrand()
#include"common.h"

using namespace ege;

void init_screen(){
	initgraph(COL * PIX + COL - 1, ROW * PIX + ROW - 1 + 16); //16 for the first line.
}

void print_screen(int iter, int state[COL][ROW]){
    int i, j;
	
	setcolor(RED);
    setfont(10, 5, "Fixedsys");
    xyprintf(0, 0, "%d           ", iter);
    
	for (i = 0; i < COL; i++)
	    for (j = 0; j < ROW; j++) {
   	        if (state[i][j]) setfillcolor(BLUE);
		    else setfillcolor(WHITE);
	        bar(i * (PIX + 1), 16 + j * (PIX + 1), i * (PIX + 1) + (PIX - 1), 16 + j * (PIX + 1) + (PIX - 1));
	    }
	
	Sleep(DELAY_MS);
}

int mygetch(){
	return getch();
}

void cleanup_screen(){
	closegraph();
}

