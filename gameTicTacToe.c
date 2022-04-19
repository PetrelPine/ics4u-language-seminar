/*
 * Tic Tac Toe Game (C)
 * Language Seminar Assignment
 * Written by PetrelPine
 * https://github.com/PetrelPine/ics4u-language-seminar
 */

/* include header files */
#include <stdio.h>
#include <string.h>

/* macro instructions */
// for output styles
// ?0 black; ?1 red; ?2 green; ?3 yellow; ?4 blue; ?5 purple; ?6 cyan; ?7 white
// 3? foreground; 4? background
// 0 default; 1 bold; 2 brightness half; 4 underline; 5 flashing; 7 reverse
#define PRINT_FONT_RED printf("\033[31m"); // foreground red
#define PRINT_FONT_YEL printf("\033[33m"); // foreground yellow
#define PRINT_FONT_BLU printf("\033[34m"); // foreground blue
#define PRINT_ATTR_REC printf("\033[0m");  // default
// for the game
#define boardLen 10    // how many positions on the board (+1)
#define boardLineLen 4 // how many positions in one line of board (+1)

/* globe variables of the game */
char board[boardLen] = "123456789"; // initialize the board of the game
char turn = 'X';                    // indicate whose turn is ('X' or 'O')
char winner = 'U';                  // indicate who is the winner ('U'(undetermined), 'D'(draw), 'X' or 'O')

/* declarations of functions */
void setLine(char[boardLineLen], int, int, int); // for checkWinner function, set the checking string (char array)
char checkWinner();        // check if the game is over and try to find the winner, return the winner status
void printBoardChar(char); // print one position of the board
void printBoardLine(int);  // print one line of the board
void printBoard();         // print the whole board

// main function
int main()
{
    printf("Welcome to 3x3 Tic Tac Toe.\n");
    printBoard();
    printf("X will play first. Enter a slot number to place X in: ");

    char input[100] = {0}; // user input
    int num;               // the slot number that the user takes in a round

    // the winner is undetermined
    while (winner == 'U')
    {
        scanf("%s", input);

        // for number n (10 <= n <= 99)
        if (input[1] - 48 >= 0 && input[1] - 48 <= 9)
            num = (input[0] - 48) * 10 + (input[1] - 48);
        // for number n (1 <= n <= 9)
        else
            num = input[0] - 48;

        // printf("The number you have typed: %d\n", num);

        // check number validity
        if (!(num >= 1 && num <= 9))
        {
            PRINT_FONT_RED // set foreground red
            printf("Invalid input, please re-enter slot number: ");
            PRINT_ATTR_REC // reset output format
            continue;
        }

        // the number is not taken
        if (board[num - 1] == (char)num + 48)
        {
            board[num - 1] = turn; // update board
            if (turn == 'X')       // change side
                turn = 'O';
            else
                turn = 'X';
            printBoard();           // print board
            winner = checkWinner(); // try to find the winner
        }
        // the number is taken
        else
        {
            PRINT_FONT_RED // set foreground red
            printf("Slot already taken, please re-enter slot number: ");
            PRINT_ATTR_REC // reset output format
            continue;
        }

        // the winner is determined --> the game is finished
        if (winner != 'U')
        {
            // it is draw
            if (winner == 'D')
                printf("It's a draw! Thanks for playing.\n");
            // there is a winner
            else
                printf("Congratulations, %c has won! Thanks for playing.\n", winner);
        }
    }

    return 0;
}

// for checkWinner function, set the checking string (char array)
void setLine(char ln[boardLineLen], int n1, int n2, int n3)
{
    ln[0] = board[n1];
    ln[1] = board[n2];
    ln[2] = board[n3];
}

// check if the game is over and try to find the winner, return the winner status
char checkWinner()
{
    // initialize the checking string (char array)
    char line[boardLineLen] = {0};

    // check every pattern to find the winner
    for (int a = 0; a < 8; a++)
    {
        switch (a)
        {
        case 0:
            setLine(line, 0, 1, 2); // row 1
            break;
        case 1:
            setLine(line, 3, 4, 5); // row 2
            break;
        case 2:
            setLine(line, 6, 7, 8); // row 3
            break;
        case 3:
            setLine(line, 0, 3, 6); // column 1
            break;
        case 4:
            setLine(line, 1, 4, 7); // column 2
            break;
        case 5:
            setLine(line, 2, 5, 8); // column 3
            break;
        case 6:
            setLine(line, 0, 4, 8); // top left to bottom right
            break;
        case 7:
            setLine(line, 2, 4, 6); // top right to bottom left
            break;
        default:;
        }

        // check if X wins
        if (strcmp(line, "XXX") == 0)
            return 'X';

        // check if O wins
        if (strcmp(line, "OOO") == 0)
            return 'O';
    }

    // check if draw
    for (int i = 0; i < boardLen - 1; i++)
    {
        // board still has empty spaces (numbers)
        if (board[i] == (char)(i + 49))
            break;
        // board is full, it's a draw case
        else if (i == 8)
            return 'D'; // draw case
    }

    printf("%c's turn, please enter a slot number to place %c in: ", turn, turn);

    return 'U'; // undetermined case
}

// print one position of the board
void printBoardChar(char pos)
{
    if (pos == 'X') {
        PRINT_FONT_BLU // set foregound blue
    }
    else if (pos == 'O') {
        PRINT_FONT_YEL // set foregound yellow
    }

    printf("%c", pos); // print the character
    PRINT_ATTR_REC     // reset output format
}

// print one line of the board
void printBoardLine(int line_num)
{
    int start_pos = (line_num - 1) * (boardLineLen - 1);
    printf("| ");
    for (int i = start_pos; i < start_pos + boardLineLen - 1; i++)
    {
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
void printBoard()
{
    printf("|---|---|---|\n");
    printBoardLine(1);
    printf("|-----------|\n");
    printBoardLine(2);
    printf("|-----------|\n");
    printBoardLine(3);
    printf("|---|---|---|\n\n");
}
