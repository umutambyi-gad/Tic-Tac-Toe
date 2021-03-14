#include <stdbool.h>


#define LENGTH 3
#define START 0


#if defined(_WIN32) || defined(_WIN64)
  #define clrscr() system("cls");
#else
  #define clrscr() system("clear");
#endif


extern void displayStatus();
extern void displayInstructions();
extern void displayBoard();
extern void humanMove();
extern void computerMove();
extern void wait();
extern bool gameOver();


void play();


int main() {
    play();
	return 0;
}


void play() {
	char board[][LENGTH] = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};

	clrscr();
    displayStatus(START);
    displayInstructions();

    do {
    	if (gameOver(board) == false) {
    		humanMove(board);
    		displayBoard(board);
    		wait(1);
    	} else {
    		break;
    	}
    	if (gameOver(board) == false) {
    		computerMove(board);
    		wait(1);
    		displayBoard(board);
    	} else {
    		break;
    	}
    } while(gameOver(board) == false);
}
