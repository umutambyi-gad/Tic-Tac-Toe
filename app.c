#include <stdio.h>
#include <stdbool.h>

#define START 0
#define LOST -1
#define TIE 1
#define WIN 2

#define display(title) ({int i; for (i = 0; i < sizeof(title) / sizeof(*title); i++) printf("%s", title[i].characters);})

#if defined(_WIN32) && defined(_WIN64)
    #define clrscr() system("cls");
#else
    #define clrscr() system("clear");
#endif

typedef struct Title {char* characters; } Title;

void displayStatus(int status);
void displayInstructions();
void displayBoard(char gameBoard[][3]);
bool checkRows(char gameBoard[][3]);
bool checkCols(char gameBoard[][3]);
bool checkDiags(char gameBoard[][3]);
bool gameOver(char gameBoard[][3]);

int main() {
	clrscr();
    displayStatus(START);
    displayInstructions();
    return 0;
}

void displayBoard(char gameBoard[][3]) {
    printf("\t\t  %c  |  %c  |  %c  \n", gameBoard[0][0], gameBoard[0][1], gameBoard[0][2]);
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


bool gameOver(char gameBoard[][3]) {
	int rows, cols;
	bool endPlay = false;
	for (rows = 0; rows < 3; rows++) {
		for (cols = 0; cols < 3; cols++) {
			if (gameBoard[rows][cols] != ' ') endPlay = true;
		}
	}
	return endPlay;
}

bool checkRows(char gameBoard[][3]) {
	int cell;
	bool endPlay = false;
	for (cell = 0; cell < 3; cell++) {
		if (gameBoard[cell][0] == gameBoard[cell][1] && gameBoard[cell][1] == gameBoard[cell][2]
			&& gameBoard[cell][0] != ' ') endPlay = true;
	}
	return endPlay;
}
