#include <stdbool.h>



#define LENGTH 3 // Length of columns or rows of the tic tac toe board
#define START 0


/*
Macros for clearing the console before starting the game didn't used the default one defined in <conio.h>
because conio is not standard library.
*/

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
    /*
    Empty board for the tic tac toe game
    */
	char board[][LENGTH] = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};

	clrscr(); // Clear screen before starting
    displayStatus(START); // Display the name of the game
    displayInstructions(); // Display instructions of the game

    /*
    End game while only gameOver() function returns true notice that gameOver() function will return true
    if tie or win detected
    */
    do {
    	if (gameOver(board) == false) {
    		humanMove(board); // Call human move function to make person play
    		displayBoard(board); // Display board after the human played
    		wait(1); // Wait one second 
    	} else {
    		break;
    	}
    	if (gameOver(board) == false) {
    		computerMove(board); // Call human move function to make computer play
    		wait(1);
    		displayBoard(board);
    	} else {
    		break;
    	}
    } while(gameOver(board) == false);
}
