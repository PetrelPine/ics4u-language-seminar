/*
 * Tutorial - Hello World
 * Language Seminar Assignment
 * Written by PetrelPine
 * https://github.com/PetrelPine/ics4u-language-seminar
 */

// This directive is read by the preprocessor and the preprocessor will insert the content 
// of the user-defined or system header file into the current program (here is stdio.h).
#include <stdio.h>

// ¡°int¡± means the function will return an integer value.
// ¡°main¡± is the function name. The main function is very important because
// it is the entry point of the program, the computer doesn¡¯t know where to start
// executing the code without the ¡°main¡± function.
int main()
{ // The curly brackets are used to indicate a block of code (here it wraps up the code inside the main function).
	
	printf("Hello World!"); // a function named printf, defined in stdio.h

	return 0; // indicated the end of the main function, exit code 0 here means the execution is successful.
}
