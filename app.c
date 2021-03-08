#include <stdio.h>

typedef struct Title {char* characters; } Title;

void displayTitle();
void displayBoard();

int main() {
    displayTitle();
    displayBoard();
    return 0;
}

void displayTitle() {
    int i;
    Title title[] = {
        {"\n"},
        {"_______ _        _______           _______ \n"},
        {"|__   __(_)      |__   __|         |__   __| \n"},
        {"   | |   _  ___     | | __ _  ___     | | ___   ___ \n"},
        {"   | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\ \n"},
        {"   | |  | | (__     | | (_| | (__     | | (_) |  __/ \n"},
        {"   |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\___| \n\n\n"}
    };
    for (i = 0; i < sizeof(title) / sizeof(*title); i++) printf("%s", title[i].characters);
}

void displayBoard() {
    printf("\t\t    |   |   \n");
    printf("\t\t--------------\n"); 
    printf("\t\t    |   |   \n"); 
    printf("\t\t--------------\n"); 
    printf("\t\t    |   |   \n\n"); 
}
