/*
 * Tutorial - Pointers
 * Language Seminar Assignment
 * Written by PetrelPine
 * https://github.com/PetrelPine/ics4u-language-seminar
 */

#include <stdio.h>

int main()
{
	int  var = 20; // ordinary variable: hold values
	int* ip;       // pointer variable: hold addresses

	ip = &var; // store the address of var to pointer variable ip

	printf("var's address: %p\n", &var); // & operator is used to get the address of the variable

	printf("address stored in ip: %p\n", ip);

	printf("value of *ip: %d\n", *ip); // use the pointer variable to access the actual value

	return 0;
}
