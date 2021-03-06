#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>


#define LOST -1
#define TIE 1
#define WIN 2
#define LENGTH 3 // Length of columns or rows of the tic tac toe board


/*
Included <windows.h> on windows platiform and <unistd.h> on other platiforms
in order to use (sleep, Sleep) functions
*/
#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
#else
	#include <unistd.h>
#endif


/*
Function for displaying 3x3 game board which takes char array as an argument
*/
void displayBoard(char board[][LENGTH]) {
	int rows;
	for (rows = 0; rows < LENGTH; rows++) {
		if (rows == 0) printf("\n");
		printf("\t\t  %c  |  %c  |  %c  \n", board[rows][0], board[rows][1], board[rows][2]);
		if (!(rows == LENGTH - 1)) printf("\t\t-----------------\n"); // display dashes except at the last iteration
	}
	printf("\n");
}


/*
Funcion for displaying instructions to the user
*/
void displayInstructions() {
	int rows, cell;
	char move;
    printf("1. The game is played on a grid that's 3 squares by 3 squares(3x3).\n\n");
    printf("2. You are x, computer is O. Players take turns putting their marks in empty squares.\n\n");
    printf("3. The first player to get 3 of her/his marks in a row (up, down, across, or diagonally) is the winner.\n\n");
    printf("4. When all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie.\n\n");

    /*
    Show how board is look like and numbers related to every cell
    */
    for (rows = 0, cell = 1; rows < LENGTH, cell < LENGTH * LENGTH; rows++, cell += 3) {
    	printf("\t\t\t  %d  |  %d  |  %d  \n", cell, cell + 1, cell + 2);
    	if (!(rows == LENGTH - 1)) printf("\t\t\t----------------\n");
    }
    printf("\n--------------        -------------------        -----------------\n\n");
}


/*
Display what's goin' on may be if the game is starting or if there is winner, looser or if they tie
*/
void displayStatus(int status) {
    if (status == 0) {
        printf("\n"
        " _______ _        _______           _______ \n"
        "|__   __(_)      |__   __|         |__   __| \n"
        "   | |   _  ___     | | __ _  ___     | | ___   ___ \n"
        "   | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\ \n"
        "   | |  | | (__     | | (_| | (__     | | (_) |  __/ \n"
        "   |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\___| \n\n\n");
    } else if (status == -1) {
	    printf("\n"
        " ___    ___              _                        _ \n"
        " \\  \\  /  /             | |                      | | \n"
        "  \\  \\/  /__  _    _    | |        ___          _| |___ \n"
        "   \\   /  _ \\| |  | |   | |       / _ \\ =======|_   ___| \n"
        "    | |  (_) | |__| |   | |_____ | (_) |   |==   | |____ \n"
        "    |_| \\___/|______|   |_______| \\___/ ======|  |______| \n\n\n");
    } else if (status == 1) {
        printf("\n"
        " ___    ___             _______ _  \n"
        " \\  \\  /  /            |__   __(_) \n"
        "  \\  \\/  /__  _    _      | |   _  ___ \n"
        "   \\   /  _ \\| |  | |     | |  | |/ _ \\ \n"
        "    | |  (_) | |__| |     | |  | |  __/ \n"
        "    |_| \\___/|______|     |_|  |_|\\___| \n\n\n");
    } else if (status == 2) {
        printf("\n"
        " ___    ___           __               __ _ \n"
        " \\  \\  /  /           \\ \\             / /(_) \n"
        "  \\  \\/  /__  _    _   \\ \\    ___    / /  _ ^^_____ \n"
        "   \\   /  _ \\| |  | |   \\ \\  / _ \\  / /  | ||  ___  |\n"
        "    | |  (_) | |__| |    \\ \\/ / \\ \\/ /   | || |   | |  \n"
        "    |_| \\___/|______|     \\__/   \\__/    |_||_|   |_|  \n\n\n");
    }
}


/*
Function for delaying or sleep seconds that is equal to the argument that passed in while
function calling
*/
void wait(int seconds) {
    #if defined(_WIN32) || defined(_WIN64)
        Sleep(1000 * seconds);
    #else
        sleep(seconds);
    #endif
}


/*
Function to check if there is any row that have been crossed by the same token and return true within showing who won or lost
otherwise returns false
*/
bool checkRows(char board[][LENGTH]) {
	int row;
	bool end = false;
	for (row = 0; row < LENGTH; row++) {
		/*
		Check if rows have been crossed by the same token
		*/
		if (board[row][0] == board[row][1] && board[row][1] == board[row][2]
			&& board[row][0] != ' ') {
			if (board[row][0] == 'x') {
				displayStatus(WIN); // If there is 3 consective 'x' in rows show human that is the winner
			} else {
				displayStatus(LOST); // Else show human that is the looser
			}
			end = true; // Set end to true if there is winner or looser
		}
	}
	return end;
}


/*
Function to check if there is any column that have been crossed by the same token and return true within showing who won or lost
otherwise returns false
*/
bool checkCols(char board[][LENGTH]) {
	int row;
	bool end = false;
	for (row = 0; row < LENGTH; row++) {
		/*
		Check if columns have been crossed by the same token
		*/
		if (board[0][row] == board[1][row] && board[1][row] == board[2][row]
			&& board[0][row] != ' ') {
			if (board[0][row] == 'x') {
				displayStatus(WIN); // If there is 3 consective 'x' in columns show human that is the winner
			} else {
				displayStatus(LOST); // Else show human that is the looser
			}
			end = true; // Set end to true if there is winner or looser
		}
	}
	return end;
}


/*
Function to check if there is any diagonal that have been crossed by the same token and return true within showing who won or lost
otherwise returns false
*/
bool checkDiags(char board[][LENGTH]) {
	bool end = false;
	/*
	Check if the top left diagonal have been crossed by the same token
	*/
	if (board[0][0] == board[1][1] && 
        board[1][1] == board[2][2] &&  
        board[0][0] != ' ') {
		if (board[0][0] == 'x') {
			displayStatus(WIN); // If there is 3 consective 'x' in diagonal start from the top left show human that is the winner
		} else {
			displayStatus(LOST); // Else show human that is the looser
		}
		end = true; // Set end to true if there is winner or looser
	}
	/*
	Check if the top right diagonal have been crossed by the same token
	*/
    if (board[0][2] == board[1][1] && 
        board[1][1] == board[2][0] && 
        board[0][2] != ' ') {
    	if (board[0][2] == 'x') {
			displayStatus(WIN); // If there is 3 consective 'x' in diagonal start from the top right show human that is the winner
		} else {
			displayStatus(LOST); // Else show human that is the looser
		}
		end = true;
    }
    return end;
}


/*
Function for ending game by checking if checkRows, checkCols or checkDiags returns true or if all cells have been occupied
and end it within displaying that you tie
*/
bool gameOver(char board[][LENGTH]) {
	int rows, cols, count = 0;
	bool end = false;
	for (rows = 0; rows < LENGTH; rows++) {
		for (cols = 0; cols < LENGTH; cols++) {
			if (board[rows][cols] != ' ') count++;
		}
	}
	if (checkRows(board) == true) end = true;
	else if (checkCols(board) == true) end = true;
	else if (checkDiags(board) == true) end = true;
	else if (count == 9) {
		displayStatus(TIE); // Display you tie if all cells are occupied without anyone whith detail of winning
		end = true;
	}
	return end;
}


/*
Function for allowing user to play
*/
void humanMove(char board[][LENGTH]) {
	int choice, row, col;
	ENTER:
		printf("Enter number to fill board and play: ");
		scanf("%d", &choice);

	if (choice < 1 || choice > 9) {
		printf("\nPlease enter number in range of 1 and 9 and inclusive\n\n");
		goto ENTER;
	}
	
	choice = choice - 1; // Choice minus one because index is from zero
	/*
	Try to calculate which row from the choice or the number user has entered
	*/
	row = (choice > LENGTH - 1)? LENGTH - 2: 0;
	row = (choice > LENGTH + 2)? LENGTH - 1: row;

	/*
	Try to calculate which column from the choice or the number user has entered
	*/
	col = (choice > LENGTH - 1)? choice - LENGTH: choice;
	col = (choice > LENGTH + 2)? (col - LENGTH): col;

	if (board[row][col] != ' ') {
		printf("\nrow has been occupied try another number\n\n");
		goto ENTER;
	}
	board[row][col] = 'x';
}


/*
Function for handling computer move
*/
void computerMove(char board[][LENGTH]) {
	srand(time(NULL)); // Initializing random number
	
	int choice, row, col;
	ENTER:
		choice = rand() % (9 + 1); // Generating random number between 1 and 9 (Inclusive)
		choice = (choice == 0)? 1 : choice;
	
	choice = choice - 1; // Choice minus one because index is from zero
	/*
	Try to calculate which row from the choice or the number computer has entered
	*/
	row = (choice > LENGTH - 1)? LENGTH - 2: 0;
	row = (choice > LENGTH + 2)? LENGTH - 1: row;

	/*
	Try to calculate which column from the choice or the number computer has entered
	*/
	col = (choice > LENGTH - 1)? choice - LENGTH: choice;
	col = (choice > LENGTH + 2)? col - LENGTH: col;
	
	/*
	If the cell has been occupied go to regenerate another number
	*/
	if (board[row][col] != ' ') {
		goto ENTER;
	}
	printf("The computer has entered: %d\n", choice + 1); // Display which number computer has entered
	board[row][col] = 'o';
}
