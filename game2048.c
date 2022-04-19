/*
 * 2048 Game
 * Language Seminar Assignment
 * Written by PetrelPine
 * https://github.com/PetrelPine/ics4u-language-seminar
 */

// include the header files
#include <stdio.h>  // include the input and output features of C
#include <stdlib.h> // include features of C standard library
#include <time.h>   // include the time() function needed to generate random numbers

// include the header files with windows related functions
// such as clear the screen in cmd and setting the position of the cursor
#include <Shlobj.h>
#include <conio.h>
#include <direct.h>
#include <io.h>
#include <windows.h>

// file related variable
static char config_path[4096] = {0}; // configuration file path

// declaration of functions
static void cmd_encoding(); // change the encoding for cmd (to avoid display error)
static void init_game();    // initialize the game
static void loop_game();    // loop the game
static void reset_game();   // reset the game
static void release_game(); // release the game process

static int read_keyboard();

static void move_left();
static void move_right();
static void move_up();
static void move_down();

static void add_rand_num();    // generate random numbers, (only generates 2 or 4), probability ratio is set to 9:1
static void check_game_over(); // check if the game is over and update the game_status
static int get_null_count();   // get the number of empty positions on the game board
static void clear_scr();       // clear screen display
static void refresh_scr();     // refresh screen display

// global variables
static int board[4][4];  // Game panel, abstracted as a two-dimensional array
static int score;        // game score
static int best;         // game highest score
static int need_add_num; // require to generate a random number, 1 is required, 0 is not required
static int game_status;  // game is over, 1 is over, 0 is not over
static int prepare_exit; // want to quit the game, 1 is yes, 0 is no

// main function
int main(int argc, char *argv[])
{
    // cmd_encoding();
    init_game();
    loop_game();
    release_game(0);
    return 0;
}

//// use "chcp 65001" change the encoding of cmd to utf-8
// void cmd_encoding()
//{
//#ifdef WIN32
//     system("chcp 65001");
//     system("cls");
//#endif
// }

// read keyboard
int read_keyboard()
{
    return _getch();
}

// start game (infinite loop of game)
void loop_game()
{
    while (1)
    {
        int cmd = read_keyboard(); // Receive standard input stream character command

        // if want to quit the game
        if (prepare_exit)
        {
            if (cmd == 'y' || cmd == 'Y')
            {
                // clear screen before exiting
                clear_scr();
                return;
            }
            else if (cmd == 'n' || cmd == 'N')
            {
                // do not exit, continue to play
                prepare_exit = 0;
                refresh_scr();
                continue;
            }
            else
            {
                continue;
            }
        }

        // if lose the game
        if (game_status)
        {
            if (cmd == 'y' || cmd == 'Y')
            {
                // replay the game
                reset_game();
                continue;
            }
            else if (cmd == 'n' || cmd == 'N')
            {
                // clear screen before exiting
                clear_scr();
                return;
            }
            else
            {
                continue;
            }
        }

        need_add_num = 0; // Do not generate a random number by default. Set it to 1 if necessary

        // Command parsing: wasd characters represent up, left, down and right commands, q represents exit
        switch (cmd)
        {
        case 'a':
        // case 75:
            move_left();
            break;
        case 's':
        // case 80:
            move_down();
            break;
        case 'w':
        // case 72:
            move_up();
            break;
        case 'd':
        // case 77:
            move_right();
            break;
        case 'q':
        // case 27:
            prepare_exit = 1;
            break;
        default:
            continue;
        }

        // player has broken the highest score record
        if (score > best)
        {
            best = score;
            // save new best score to file
            FILE *fp = fopen(config_path, "w");
            if (fp)
            {
                fwrite(&best, sizeof(best), 1, fp);
                fclose(fp);
            }
        }

        // random numbers are generated and the screen needs to be refreshed
        if (need_add_num)
        {
            add_rand_num();
            refresh_scr();
        }
        else if (prepare_exit)
        {
            refresh_scr();
        }
    }
}

// reset the game
void reset_game()
{
    score = 0;
    need_add_num = 1;
    game_status = 0;
    prepare_exit = 0;

    // one of the two numbers that appear when the game is initialized must be 2, so randomly generates a 2 and
    // everything else are zeros
    int n = rand() % 16;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            board[i][j] = (n-- == 0 ? 2 : 0);
        }
    }

    // We've already generated a 2, and here we're regenerating a random 2 or 4 with a ratio of 9 to 1
    add_rand_num();

    // When I refresh the screen and display it, there are already two numbers on the screen by default, and the others
    // are empty (value 0).
    refresh_scr();
}

// generate random numbers
void add_rand_num()
{
    srand((unsigned int)time(0));
    int n = rand() % get_null_count(); // determine the position of the generated random number
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            // if it is the position to generate numbers
            if (board[i][j] == 0 && n-- == 0)
            {
                board[i][j] = (rand() % 10 ? 2 : 4); // Generate the numbers 2 or 4 with a probability of 9:1
                return;
            }
        }
    }
}

// get the number of empty positions
int get_null_count()
{
    int n = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            board[i][j] == 0 ? ++n : 1;
        }
    }
    return n;
}

// check if the game is over
void check_game_over()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            // Compare two adjacent elements horizontally and vertically to see if they are equal. If they are, the game
            // does not end
            if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i])
            {
                game_status = 0;
                return;
            }
        }
    }
    game_status = 1;
}

/*
 * The following four functions to realize the change algorithm of the number panel when moving up, down, left and right
 * Left and right movements are essentially the same, the only difference is that the column items are traversed in
 * opposite directions. Up and down movements are essentially the same, the only difference is that the row items
 * traverse in opposite directions. Left and up movements are essentially the same, the only difference is that the rows
 * and columns are interchanged throughout.
 */

// move left function
void move_left()
{
    // The variable i is used to traverse the subscripts of row items, and all rows are independent of each other when
    // moving
    for (int i = 0; i < 4; ++i)
    {
        // The variable j is the subscript of the column, the variable K is the subscript of the item to be compared
        // (merged), and the loop enters with k<j
        for (int j = 1, k = 0; j < 4; ++j)
        {
            if (board[i][j] > 0) // Find the first non-empty term after k, subscript j, and then there are three different situations
            {
                if (board[i][k] == board[i][j])
                {
                    // Case 1: k and J are equal, the squares are merged and the score is scored
                    score += board[i][k++] *= 2;
                    board[i][j] = 0;
                    need_add_num = 1; // generate random numbers and refresh screen
                }
                else if (board[i][k] == 0)
                {
                    // Case 2: k is empty, then assigning j to K is equivalent to moving the J block to the K block
                    board[i][k] = board[i][j];
                    board[i][j] = 0;
                    need_add_num = 1;
                }
                else
                {
                    // Case 3: the k term is not empty and is not equal to the j term. Assigning the j term to the k+1
                    // term is equivalent to moving to the position of k+1
                    board[i][++k] = board[i][j];
                    if (j != k)
                    {
                        // Determine if j and k are originally next to each other, if not, assign j to null (value 0)
                        board[i][j] = 0;
                        need_add_num = 1;
                    }
                }
            }
        }
    }
}

// move right function
void move_right()
{
    // similar to the left shift operation, the only difference is that both j and K are traversed backwards
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 2, k = 3; j >= 0; --j)
        {
            if (board[i][j] > 0)
            {
                if (board[i][k] == board[i][j])
                {
                    score += board[i][k--] *= 2;
                    board[i][j] = 0;
                    need_add_num = 1;
                }
                else if (board[i][k] == 0)
                {
                    board[i][k] = board[i][j];
                    board[i][j] = 0;
                    need_add_num = 1;
                }
                else
                {
                    board[i][--k] = board[i][j];
                    if (j != k)
                    {
                        board[i][j] = 0;
                        need_add_num = 1;
                    }
                }
            }
        }
    }
}

// move up function
void move_up()
{
    // similar to the left shift operation, the only difference is that
    // after the row and column swap traversal
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 1, k = 0; j < 4; ++j)
        {
            if (board[j][i] > 0)
            {
                if (board[k][i] == board[j][i])
                {
                    score += board[k++][i] *= 2;
                    board[j][i] = 0;
                    need_add_num = 1;
                }
                else if (board[k][i] == 0)
                {
                    board[k][i] = board[j][i];
                    board[j][i] = 0;
                    need_add_num = 1;
                }
                else
                {
                    board[++k][i] = board[j][i];
                    if (j != k)
                    {
                        board[j][i] = 0;
                        need_add_num = 1;
                    }
                }
            }
        }
    }
}

// move down function
void move_down()
{
    // similar to the left shift operation, the only difference is that
    // the rows and columns are traversed after switching, and both j and K are traversed backwards
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 2, k = 3; j >= 0; --j)
        {
            if (board[j][i] > 0)
            {
                if (board[k][i] == board[j][i])
                {
                    score += board[k--][i] *= 2;
                    board[j][i] = 0;
                    need_add_num = 1;
                }
                else if (board[k][i] == 0)
                {
                    board[k][i] = board[j][i];
                    board[j][i] = 0;
                    need_add_num = 1;
                }
                else
                {
                    board[--k][i] = board[j][i];
                    if (j != k)
                    {
                        board[j][i] = 0;
                        need_add_num = 1;
                    }
                }
            }
        }
    }
}

// clear screen
void clear_scr()
{
    // reset cursor output position clear screen to reduce flicker
    // system("cls") // back-up method
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    CONSOLE_CURSOR_INFO info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// refresh screen
void refresh_scr()
{
    clear_scr();

    printf("\n\n\n\n");
    printf("                  GAME: 2048     SCORE: %05d     BEST: %06d\n", score, best);
    printf("               --------------------------------------------------");

    // print lines and numbers
    printf("\n\n                             ---------------------\n");
    for (int i = 0; i < 4; ++i)
    {
        printf("                             |");
        for (int j = 0; j < 4; ++j)
        {
            if (board[i][j] != 0)
            {
                if (board[i][j] < 10)
                {
                    printf("  %d |", board[i][j]);
                }
                else if (board[i][j] < 100)
                {
                    printf(" %d |", board[i][j]);
                }
                else if (board[i][j] < 1000)
                {
                    printf(" %d|", board[i][j]);
                }
                else if (board[i][j] < 10000)
                {
                    printf("%4d|", board[i][j]);
                }
                else
                {
                    int n = board[i][j];
                    for (int k = 1; k < 20; ++k)
                    {
                        n = n >> 1;
                        if (n == 1)
                        {
                            printf("2^%02d|", k); // numbers larger than four digits are expressed as powers of two, such as 2^13
                            break;
                        }
                    }
                }
            }
            else
                printf("    |");
        }

        if (i < 3)
        {
            printf("\n                             |----|----|----|----|\n");
        }
        else
        {
            printf("\n                             ---------------------\n");
        }
    }
    printf("\n");
    printf("               --------------------------------------------------\n");
    printf("                  [W]:UP [S]:DOWN [A]:LEFT [D]:RIGHT [Q]:EXIT");

    if (get_null_count() == 0)
    {
        check_game_over();

        // check if the game is over
        if (game_status)
        {
            printf("\r                      GAME OVER! TRY THE GAME AGAIN? [Y/N]:     \b\b\b\b");
            CONSOLE_CURSOR_INFO info = {1, 1};
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
        }
    }

    // if want to exit the game
    if (prepare_exit)
    {
        printf("\r                   DO YOU REALLY WANT TO QUIT THE GAME? [Y/N]:   \b\b");
        
        CONSOLE_CURSOR_INFO info = {1, 1};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    }

    fflush(0); // Flush the output buffer
}

// initialize the game
void init_game()
{
    system("cls"); // clear screen

    // Get the game save path: C:\Users\UserName\AppData\Local\2048 (for Windows)
    char m_lpszDefaultDir[MAX_PATH];
    char szDocument[MAX_PATH] = {0};
    memset(m_lpszDefaultDir, 0, _MAX_PATH);
    LPITEMIDLIST pidl = NULL;
    SHGetSpecialFolderLocation(NULL, CSIDL_LOCAL_APPDATA, &pidl);
    if (pidl && SHGetPathFromIDList(pidl, szDocument))
    {
        GetShortPathName(szDocument, m_lpszDefaultDir, _MAX_PATH);
    }
    sprintf(config_path, "%s\\2048", m_lpszDefaultDir);
    if (_access(config_path, 0) == -1)
    {
        _mkdir(config_path);
    }
    sprintf(config_path, "%s\\2048\\2048.dat", m_lpszDefaultDir);

    // load the highest score of the game
    FILE *fp = fopen(config_path, "r");
    if (fp)
    {
        fread(&best, sizeof(best), 1, fp);
        fclose(fp);
    }
    else
    {
        best = 0;
        fp = fopen(config_path, "w");
        if (fp)
        {
            fwrite(&best, sizeof(best), 1, fp);
            fclose(fp);
        }
    }

    reset_game();
}

// release the game process
void release_game()
{
    system("cls");
    CONSOLE_CURSOR_INFO info = {1, 1};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    exit(0);
}
