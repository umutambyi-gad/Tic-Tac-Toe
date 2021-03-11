#include <stdio.h>
#include <stdbool.h>

#define START 0
#define LOST -1
#define TIE 1
#define WIN 2

#define display(title) ({int i; for (i = 0; i < sizeof(title) / sizeof(*title); i++) printf("%s", title[i].characters);})

#if defined(_WIN32) || defined(_WIN64)
    #define clrscr() system("cls");
	#include <windows.h>
#else
    #define clrscr() system("clear");
	#include <unistd.h>
#endif

typedef struct Title {char* characters; } Title;

void wait(int seconds);
void displayStatus(int status);
void displayInstructions();
void displayBoard(char gameBoard[][3]);
bool checkRows(char gameBoard[][3]);
bool checkCols(char gameBoard[][3]);
bool checkDiags(char gameBoard[][3]);
bool gameOver(char gameBoard[][3]);
void humanMove(char gameBoard[][3]);
void computerMove(char gameBoard[][3]);
void play();

int main() {
	clrscr();
    displayStatus(START);
    displayInstructions();
    play();
    return 0;
}

void displayBoard(char gameBoard[][3]) {
    printf("\n\n\t\t  %c  |  %c  |  %c  \n", gameBoard[0][0], gameBoard[0][1], gameBoard[0][2]);
    printf("\t\t-----------------\n");
    printf("\t\t  %c  |  %c  |  %c  \n", gameBoard[1][0], gameBoard[1][1], gameBoard[1][2]);
    printf("\t\t-----------------\n");
    printf("\t\t  %c  |  %c  |  %c  \n\n", gameBoard[2][0], gameBoard[2][1], gameBoard[2][2]);
}

void displayInstructions() {
    printf("Pick a number from 1 to 9 to fill the cell in the board as below and play\n\n");
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
	    Title title[] = {
	        {"\n"},
	        {" _______ _        _______           _______ \n"},
	        {"|__   __(_)      |__   __|         |__   __| \n"},
	        {"   | |   _  ___     | | __ _  ___     | | ___   ___ \n"},
	        {"   | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\ \n"},
	        {"   | |  | | (__     | | (_| | (__     | | (_) |  __/ \n"},
	        {"   |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\___| \n\n\n"}
	    };
	    display(title);
    } else if (status == -1) {
    	Title title[] = {
	        {"\n"},
	        {" ___    ___              _                        _ \n"},
	        {" \\  \\  /  /             | |                      | | \n"},
	        {"  \\  \\/  /__  _    _    | |        ___          _| |___ \n"},
	        {"   \\   /  _ \\| |  | |   | |       / _ \\ =======|_   ___| \n"},
	        {"    | |  (_) | |__| |   | |_____ | (_) |   |==   | |____ \n"},
	        {"    |_| \\___/|______|   |_______| \\___/ ======|  |______| \n\n\n"}
	    };
	    display(title);
    } else if (status == 1) {
    	Title title[] = {
	        {"\n"},
	        {" ___    ___             _______ _  \n"},
	        {" \\  \\  /  /            |__   __(_) \n"},
	        {"  \\  \\/  /__  _    _      | |   _  ___ \n"},
	        {"   \\   /  _ \\| |  | |     | |  | |/ _ \\ \n"},
	        {"    | |  (_) | |__| |     | |  | |  __/ \n"},
	        {"    |_| \\___/|______|     |_|  |_|\\___| \n\n\n"}
	    };
	    display(title);
    } else if (status == 2) {
    	Title title[] = {
	        {"\n"},
	        {" ___    ___           __               __ _   ___     _ \n"},
	        {" \\  \\  /  /           \\ \\             / /(_) |   \\   | | \n"},
	        {"  \\  \\/  /__  _    _   \\ \\    ___    / /  _  | |\\ \\  | | \n"},
	        {"   \\   /  _ \\| |  | |   \\ \\  / _ \\  / /  | | | | \\ \\ | | \n"},
	        {"    | |  (_) | |__| |    \\ \\/ / \\ \\/ /   | | | |  \\ \\| | \n"},
	        {"    |_| \\___/|______|     \\__/   \\__/    |_| |_|   \\___| \n\n\n"}
	    };
	    display(title);
    }
}

void wait(int seconds) {
    #if defined(_WIN32) || defined(_WIN64)
        Sleep(1000 * seconds);
    #else
        sleep(seconds);
    #endif
}

bool gameOver(char gameBoard[][3]) {
	int rows, cols, count = 0;
	bool endPlay = false;
	for (rows = 0; rows < 3; rows++) {
		for (cols = 0; cols < 3; cols++) {
			if (gameBoard[rows][cols] != ' ') count++;
		}
	}
	if (count == 9){
		displayStatus(TIE);
		endPlay = true;
	}
	else if (checkRows(gameBoard) == true) endPlay = true;
	else if (checkCols(gameBoard) == true) endPlay = true;
	else if (checkDiags(gameBoard) == true) endPlay = true;
	return endPlay;
}

bool checkRows(char gameBoard[][3]) {
	int cell;
	bool endPlay = false;
	for (cell = 0; cell < 3; cell++) {
		if (gameBoard[cell][0] == gameBoard[cell][1] && gameBoard[cell][1] == gameBoard[cell][2]
			&& gameBoard[cell][0] != ' ') {
			if (gameBoard[cell][0] == 'x') {
				displayStatus(WIN);
			} else {
				displayStatus(LOST);
			}
			endPlay = true;
		}
	}
	return endPlay;
}

bool checkCols(char gameBoard[][3]) {
	int cell;
	bool endPlay = false;
	for (cell = 0; cell < 3; cell++) {
		if (gameBoard[0][cell] == gameBoard[1][cell] && gameBoard[1][cell] == gameBoard[2][cell]
			&& gameBoard[0][cell] != ' ') {
			if (gameBoard[0][cell] == 'x') {
				displayStatus(WIN);
			} else {
				displayStatus(LOST);
			}
			endPlay = true;
		}
	}
	return endPlay;
}

bool checkDiags(char gameBoard[][3]) {
	bool endPlay = false;
	if (gameBoard[0][0] == gameBoard[1][1] && 
        gameBoard[1][1] == gameBoard[2][2] &&  
        gameBoard[0][0] != ' ') {
		if (gameBoard[0][0] == 'x') {
			displayStatus(WIN);
		} else {
			displayStatus(LOST);
		}
		endPlay = true;
	}
    if (gameBoard[0][2] == gameBoard[1][1] && 
        gameBoard[1][1] == gameBoard[2][0] && 
        gameBoard[0][2] != ' ') {
    	if (gameBoard[0][2] == 'x') {
			displayStatus(WIN);
		} else {
			displayStatus(LOST);
		}
		endPlay = true;
    }
    return endPlay;
}

void humanMove(char gameBoard[][3]) {
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

	if (gameBoard[row][col] != ' ') {
		printf("\ncell has been occupied try another number\n");
		goto ENTER;
	}
	gameBoard[row][col] = 'x';
}

void computerMove(char gameBoard[][3]) {
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
	
	if (gameBoard[row][col] != ' ') {
		goto ENTER;
	}
	printf("The computer has entered: %d\n", choice + 1);
	gameBoard[row][col] = 'o';
}


void play() {
	char gameBoard[][3] = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};
    do {
    	humanMove(gameBoard);
    	displayBoard(gameBoard);
    	wait(1);
    	computerMove(gameBoard);
    	wait(1);
    	displayBoard(gameBoard);
    } while(gameOver(gameBoard) == false);
}
