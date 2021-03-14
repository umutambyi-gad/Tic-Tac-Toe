#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define START 0
#define LOST -1
#define TIE 1
#define WIN 2

#define LENGTH 3

#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
#else
	#include <unistd.h>
#endif


void displayBoard(char board[][LENGTH]) {
	int rows;
	for (rows = 0; rows < LENGTH; rows++) {
		if (rows == 0) printf("\n");
		printf("\t\t  %c  |  %c  |  %c  \n", board[rows][0], board[rows][1], board[rows][2]);
		if (!(rows == LENGTH - 1)) printf("\t\t-----------------\n");
	}
	printf("\n");
}

void displayInstructions() {
	int rows, cell;
	char move;
    printf("1. The game is played on a grid that's 3 squares by 3 squares(3x3).\n\n");
    printf("2. You are x, computer is O. Players take turns putting their marks in empty squares.\n\n");
    printf("3. The first player to get 3 of her marks in a row (up, down, across, or diagonally) is the winner.\n\n");
    printf("4. When all 9 squares are full, the game is over. If no player has 3 marks in a row, the game ends in a tie.\n\n");

    for (rows = 0, cell = 1; rows < LENGTH, cell < LENGTH * LENGTH; rows++, cell += 3) {
    	printf("\t\t\t  %d  |  %d  |  %d  \n", cell, cell + 1, cell + 2);
    	if (!(rows == LENGTH - 1)) printf("\t\t\t----------------\n");
    }
    printf("\n--------------        -------------------        -----------------\n\n");
}

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

void wait(int seconds) {
    #if defined(_WIN32) || defined(_WIN64)
        Sleep(1000 * seconds);
    #else
        sleep(seconds);
    #endif
}


bool checkRows(char board[][LENGTH]) {
	int row;
	bool end = false;
	for (row = 0; row < LENGTH; row++) {
		if (board[row][0] == board[row][1] && board[row][1] == board[row][2]
			&& board[row][0] != ' ') {
			if (board[row][0] == 'x') {
				displayStatus(WIN);
			} else {
				displayStatus(LOST);
			}
			end = true;
		}
	}
	return end;
}

bool checkCols(char board[][LENGTH]) {
	int row;
	bool end = false;
	for (row = 0; row < LENGTH; row++) {
		if (board[0][row] == board[1][row] && board[1][row] == board[2][row]
			&& board[0][row] != ' ') {
			if (board[0][row] == 'x') {
				displayStatus(WIN);
			} else {
				displayStatus(LOST);
			}
			end = true;
		}
	}
	return end;
}

bool checkDiags(char board[][LENGTH]) {
	bool end = false;
	if (board[0][0] == board[1][1] && 
        board[1][1] == board[2][2] &&  
        board[0][0] != ' ') {
		if (board[0][0] == 'x') {
			displayStatus(WIN);
		} else {
			displayStatus(LOST);
		}
		end = true;
	}
    if (board[0][2] == board[1][1] && 
        board[1][1] == board[2][0] && 
        board[0][2] != ' ') {
    	if (board[0][2] == 'x') {
			displayStatus(WIN);
		} else {
			displayStatus(LOST);
		}
		end = true;
    }
    return end;
}

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
		displayStatus(TIE);
		end = true;
	}
	return end;
}

void humanMove(char board[][LENGTH]) {
	int choice, row, col;
	ENTER:
		printf("Enter number to fill board and play: ");
		scanf("%d", &choice);

	if (choice < 1 || choice > 9) {
		printf("\nPlease enter number in range of 1 and 9 and inclusive\n\n");
		goto ENTER;
	}
	
	choice = choice - 1;
	row = (choice > LENGTH - 1)? LENGTH - 2: 0;
	row = (choice > LENGTH + 2)? LENGTH - 1: row;

	col = (choice > LENGTH - 1)? choice - LENGTH: choice;
	col = (choice > LENGTH + 2)? (col - LENGTH): col;

	if (board[row][col] != ' ') {
		printf("\nrow has been occupied try another number\n\n");
		goto ENTER;
	}
	board[row][col] = 'x';
}

void computerMove(char board[][LENGTH]) {
	srand(time(NULL));
	
	int choice, row, col;
	ENTER:
		choice = rand() % (9 + 1);
		choice = (choice == 0)? 1 : choice;
	
	choice = choice - 1;
	row = (choice > LENGTH - 1)? LENGTH - 2: 0;
	row = (choice > LENGTH + 2)? LENGTH - 1: row;

	col = (choice > LENGTH - 1)? choice - LENGTH: choice;
	col = (choice > LENGTH + 2)? col - LENGTH: col;
	
	if (board[row][col] != ' ') {
		goto ENTER;
	}
	printf("The computer has entered: %d\n", choice + 1);
	board[row][col] = 'o';
}
