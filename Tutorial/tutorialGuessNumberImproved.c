/*
 * Tutorial - Guess Number Improved
 * Language Seminar Assignment
 * Written by PetrelPine
 * https://github.com/PetrelPine/ics4u-language-seminar
 */

#include <stdio.h>
#include <stdlib.h> // srand, atoi
#include <time.h>   // time

int main()
{
    int lowerBound = 1, upperBound = 10; // set the boundary of random numbers

    // generate a random number (integer) as the answer
    // use time as the seed to rearrange the random numbers, this is to
    // make sure every time you run this program, it will generate a new random number
    srand((unsigned)time(NULL));
    int answer = rand() % upperBound + 1; // (random number range: 1 ~ 10)

    // printf("TEST: The answer is %d\n", answer); // test

    char guess[30] = {0}; // store the player input
    int guessNum = 0;     // store the number player guessed

    // do while loop, stops until the player gets the answer
    do
    {
        printf("Enter the number you guessed (range %d to %d): ", lowerBound, upperBound);
        scanf("%s", guess);
        // printf("The number you entered: %s\n", guess);

        // convert the input from string to integer
        guessNum = atoi(guess);
        // if no valid conversion could be performed, atoi returns zero
        if (guessNum == 0)
        {
            printf("Invalid input!\n\n");
            continue; // start the next round
        }

        // check if the player gets the answer
        if (guessNum > answer)
        {
            printf("Too big! Try a smaller number.\n\n");
        }
        else if (guessNum < answer)
        {
            printf("Too small! Try a bigger number.\n\n");
        }
        else // guessNum == answer
        {
            printf("Congratulations! You got the correct answer.\n\n");
        }
    } while (guessNum != answer);

    return 0;
}
