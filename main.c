// LANGUAGE SEMINAR ASSIGNMENT
// ICS4U WILSON
// WRITTEN BY PETRELPINE
// https://github.com/PetrelPine/ics4u-language-seminar

/* include header files */
#include <stdio.h>
#include <string.h>

/* macro instructions */
# define REFRESH_DEBUGGER fflush(stdout);  // fix the debugger display problem

// for color print
// set output foreground
#define PRINT_FONT_BLA  printf("\033[30m"); // black
#define PRINT_FONT_RED  printf("\033[31m"); // red
#define PRINT_FONT_GRE  printf("\033[32m"); // green
#define PRINT_FONT_YEL  printf("\033[33m"); // yellow
#define PRINT_FONT_BLU  printf("\033[34m"); // blue
#define PRINT_FONT_PUR  printf("\033[35m"); // purple
#define PRINT_FONT_CYA  printf("\033[36m"); // cyan
#define PRINT_FONT_WHI  printf("\033[37m"); // white
// set output background
#define PRINT_BACK_BLA  printf("\033[40m"); // black
#define PRINT_BACK_RED  printf("\033[41m"); // red
#define PRINT_BACK_GRE  printf("\033[42m"); // green
#define PRINT_BACK_YEL  printf("\033[43m"); // yellow
#define PRINT_BACK_BLU  printf("\033[44m"); // blue
#define PRINT_BACK_PUR  printf("\033[45m"); // purple
#define PRINT_BACK_CYA  printf("\033[46m"); // cyan
#define PRINT_BACK_WHI  printf("\033[47m"); // white
// set output attribute
#define PRINT_ATTR_REC  printf("\033[0m");  // default
#define PRINT_ATTR_BOL  printf("\033[1m");  // bold
#define PRINT_ATTR_LIG  printf("\033[2m");  // brightness half
#define PRINT_ATTR_LIN  printf("\033[4m");  // underline
#define PRINT_ATTR_GLI  printf("\033[5m");  // flashing
#define PRINT_ATTR_REV  printf("\033[7m");  // reverse
#define PRINT_ATTR_THI  printf("\033[22m"); // density
#define PRINT_ATTR_ULI  printf("\033[24m"); // underline off
#define PRINT_ATTR_UGL  printf("\033[25m"); // flashing off
#define PRINT_ATTR_URE  printf("\033[27m"); // reverse off

// for the game
#define boardLen 10  // how many positions on the board (+1)
#define boardLineLen 4  // how many positions in one line of board (+1)


// globe variables of the game
char board[boardLen] = "123456789";  // initialize the board of the game
char turn = 'X';  // indicate whose turn is ('X' or 'O')
char winner = 'U';  // indicate who is the winner ('U'(undetermined), 'D'(draw), 'X' or 'O')


// declarations of functions
void setLine(char[], int, int, int);  // for checkWinner function, set the checking string (char array)
char checkWinner();  // check if the game is over and try to find the winner, return the winner status

void printBoardChar(char);  // print one position of the board
void printBoardLine(int);  // print one line of the board
void printBoard();  // print the whole board


// main function
int main() {
    printf("Welcome to 3x3 Tic Tac Toe.\n");
    REFRESH_DEBUGGER
    
    printBoard();
    printf("X will play first. Enter a slot number to place X in: ");
    REFRESH_DEBUGGER
    
    char input[100] = {0};  // user input
    int num;  // the slot number that the user takes in a round
    
    // the winner is undetermined
    while (winner == 'U') {
        scanf("%s", input);
        
        // for number n (10 <= n <= 99)
        if (input[1] - 48 >= 0 && input[1] - 48 <= 9)
            num = (input[0] - 48) * 10 + (input[1] - 48);
        // for number n (1 <= n <= 9)
        else
            num = input[0] - 48;
        
        // printf("The number you have typed: %d\n", num);
        // REFRESH_DEBUGGER
        
        // check number validity
        if (!(num >= 1 && num <= 9)) {
            PRINT_FONT_RED
            printf("Invalid input, please re-enter slot number: ");
            PRINT_ATTR_REC
            REFRESH_DEBUGGER
            continue;
        }
        
        // the number is not taken
        if (board[num - 1] == (char) num + 48) {
            board[num - 1] = turn;  // update board
            if (turn == 'X') turn = 'O'; else turn = 'X';  // change side
            printBoard();  // print board
            winner = checkWinner();  // try to find the winner
        }
        // the number is taken
        else {
            PRINT_FONT_RED
            printf("Slot already taken, please re-enter slot number: ");
            PRINT_ATTR_REC
            REFRESH_DEBUGGER
            continue;
        }
        
        // the winner is determined --> the game is finished
        if (winner != 'U') {
            // it is draw
            if (winner == 'D') {
                printf("It's a draw! Thanks for playing.\n");
                REFRESH_DEBUGGER
            }
            // there is a winner
            else {
                printf("Congratulations, %c has won! Thanks for playing.\n", winner);
                REFRESH_DEBUGGER
            }
        }
    }
    
    return 0;
}

// for checkWinner function, set the checking string (char array)
void setLine(char ln[boardLineLen], int n1, int n2, int n3) {
    ln[0] = board[n1];
    ln[1] = board[n2];
    ln[2] = board[n3];
}

// check if the game is over and try to find the winner, return the winner status
char checkWinner() {
    // initialize the checking string (char array)
    char line[boardLineLen] = {0};
    
    // check every pattern to find the winner
    for (int a = 0; a < 8; a++) {
        switch (a) {
            case 0:
                setLine(line, 0, 1, 2);  // row 1
                break;
            case 1:
                setLine(line, 3, 4, 5);  // row 2
                break;
            case 2:
                setLine(line, 6, 7, 8);  // row 3
                break;
            case 3:
                setLine(line, 0, 3, 6);  // column 1
                break;
            case 4:
                setLine(line, 1, 4, 7);  // column 2
                break;
            case 5:
                setLine(line, 2, 5, 8);  // column 3
                break;
            case 6:
                setLine(line, 0, 4, 8);  // top left to bottom right
                break;
            case 7:
                setLine(line, 2, 4, 6);  // top right to bottom left
                break;
            default:;
        }
        
        // check if X wins
        if (strcmp(line, "XXX") == 0) return 'X';
        
        // check if O wins
        if (strcmp(line, "OOO") == 0) return 'O';
        
        // check if draw
        for (int i = 0; i < boardLen; i++) {
            // board still has empty spaces (numbers)
            if (board[i] == (char)(i + 49)) break;
            // board is full, it's a draw case
            else if (i == 8) return 'D';  // draw
        }
    }
    
    printf("%c's turn; enter a slot number to place %c in: ", turn, turn);
    REFRESH_DEBUGGER
    
    return 'U';  // undetermined
}

// print one position of the board
void printBoardChar(char pos) {
    if (pos == 'X') PRINT_FONT_BLU  // set blue
    else if (pos == 'O') PRINT_FONT_YEL  // set yellow
    printf("%c", pos);
    PRINT_ATTR_REC  // reset
}

// print one line of the board
void printBoardLine(int start_pos) {
    printf("| ");
    for (int i = start_pos; i < start_pos + boardLineLen - 1; i++) {
        printBoardChar(board[i]);
        printf(" | ");
    }
    printf("\n");
}

/*
board example
|---|---|---|
| 1 | 2 | 3 |
|-----------|
| 4 | 5 | 6 |
|-----------|
| 7 | 8 | 9 |
|---|---|---|
 */
// print the whole board
void printBoard() {
    printf("|---|---|---|\n");
    printBoardLine(0);
    printf("|-----------|\n");
    printBoardLine(3);
    printf("|-----------|\n");
    printBoardLine(6);
    printf("|---|---|---|\n\n");
    
    REFRESH_DEBUGGER
}
