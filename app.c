#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define START 0
#define LOST -1
#define TIE 1
#define WIN 2

#if defined(_WIN32) || defined(_WIN64)
    #define clrscr() system("cls");
	#include <windows.h>
#else
    #define clrscr() system("clear");
	#include <unistd.h>
#endif


void displayBoard(char board[][3]) {
    printf("\n\n\t\t  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t-----------------\n");
    printf("\t\t  %c  |  %c  |  %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t-----------------\n");
    printf("\t\t  %c  |  %c  |  %c  \n\n", board[2][0], board[2][1], board[2][2]);
}

void displayInstructions() {
    printf("Pick a number from 1 to 9 to fill the row in the board as below and play\n\n");
    printf("\t\t\t  1  |  2  |  3  \n");
    printf("\t\t\t----------------\n");
    printf("\t\t\t  4  |  5  |  6  \n");
    printf("\t\t\t----------------\n");
    printf("\t\t\t  7  |  8  |  9  \n\n");
    printf("--------------        -------------------        -----------------\n\n");
}

void displayStatus(int status) {
    int i;
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
	        " ___    ___           __               __ _   ___     _ \n"
	        " \\  \\  /  /           \\ \\             / /(_) |   \\   | | \n"
	        "  \\  \\/  /__  _    _   \\ \\    ___    / /  _  | |\\ \\  | | \n"
	        "   \\   /  _ \\| |  | |   \\ \\  / _ \\  / /  | | | | \\ \\ | | \n"
	        "    | |  (_) | |__| |    \\ \\/ / \\ \\/ /   | | | |  \\ \\| | \n"
	        "    |_| \\___/|______|     \\__/   \\__/    |_| |_|   \\___| \n\n\n");
    }
}

void wait(int seconds) {
    #if defined(_WIN32) || defined(_WIN64)
        Sleep(1000 * seconds);
    #else
        sleep(seconds);
    #endif
}


bool checkRows(char board[][3]) {
	int row;
	bool end = false;
	for (row = 0; row < 3; row++) {
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

bool checkCols(char board[][3]) {
	int row;
	bool end = false;
	for (row = 0; row < 3; row++) {
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

bool checkDiags(char board[][3]) {
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

bool gameOver(char board[][3]) {
	int rows, cols, count = 0;
	bool end = false;
	for (rows = 0; rows < 3; rows++) {
		for (cols = 0; cols < 3; cols++) {
			if (board[rows][cols] != ' ') count++;
		}
	}
	if (count == 9){
		displayStatus(TIE);
		end = true;
	}
	else if (checkRows(board) == true) end = true;
	else if (checkCols(board) == true) end = true;
	else if (checkDiags(board) == true) end = true;
	return end;
}

void humanMove(char board[][3]) {
	int choice, row, col;
	ENTER:
		printf("Enter number to fill play: ");
		scanf("%d", &choice);

	if (choice < 1 || choice > 9) {
		printf("\nPlease enter number in range of 1 and 9 and inclusive\n\n");
		goto ENTER;
	}
	
	choice = choice - 1;
	row = (choice > 2)? 1: 0;
	row = (choice > 5)? 2: row;

	col = (choice > 2)? choice - 3: choice;
	col = (choice > 5)? (col - 3): col;

	if (board[row][col] != ' ') {
		printf("\nrow has been occupied try another number\n");
		goto ENTER;
	}
	board[row][col] = 'x';
}

void computerMove(char board[][3]) {
	srand(time(NULL));
	
	int choice, row, col;
	ENTER:
		choice = rand() % (9 + 1);
		choice = (choice == 0)? 1 : choice;
	
	choice = choice - 1;
	row = (choice > 2)? 1: 0;
	row = (choice > 5)? 2: row;

	col = (choice > 2)? choice - 3: choice;
	col = (choice > 5)? (col - 3): col;
	
	if (board[row][col] != ' ') {
		goto ENTER;
	}
	printf("The computer has entered: %d\n", choice + 1);
	board[row][col] = 'o';
}


void play() {
	char board[][3] = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};
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

int main() {
	clrscr();
    displayStatus(START);
    displayInstructions();
    play();
    return 0;
}
