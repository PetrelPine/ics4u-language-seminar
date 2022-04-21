/*
 * Tutorial - Guess Number
 * Language Seminar Assignment
 * Written by PetrelPine
 * https://github.com/PetrelPine/ics4u-language-seminar
 */

#include <stdio.h>
#include <stdlib.h> // srand
#include <time.h> // time

int main()
{
    int lowerBound = 1, upperBound = 10; // set the boundary of random numbers

    // generate a random number (integer) as the answer
    // use time as the seed to rearrange the random numbers, this is to 
    // make sure every time you run this program, it will generate a new random number
    srand((unsigned)time(NULL)); 
    int answer = rand() % upperBound + 1; // (random number range: 1 ~ 30)

    // printf("TEST: The answer is %d\n", answer); // test

    int guess = -1; // store the user input

    // do while loop, stops until the player gets the answer
    do
    {
        printf("Enter the number you guessed: ");
        scanf("%d", &guess);
        // printf("The number you entered: %d\n", guess);

        // check if the player gets the answer
        if (guess > answer)
        {
            printf("Too big! Try a smaller number.\n\n");
        }
        else if (guess < answer)
        {
            printf("Too small! Try a bigger number.\n\n");
        }
        else // guess == answer
        {
            printf("Congratulations! You got the correct answer.\n\n");
        }
    } while (guess != answer);

    return 0;
}
