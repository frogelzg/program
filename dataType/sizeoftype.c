/*
 * This a program for showing the size of each data type in this machine.
 */

#include <stdio.h>

int main()
{
	printf("unsigned char: %ld\n", sizeof(unsigned char));
	printf("char：　%ld\n", sizeof(char));
	printf("unsigned short：　%ld\n", sizeof(unsigned short));
	printf("short：　%ld\n", sizeof(short));
	printf("unsigned int：　%ld\n", sizeof(unsigned int));
	printf("int：　%ld\n", sizeof(int));
	printf("unsigned long：　%ld\n", sizeof(unsigned long));
	printf("long：　%ld\n", sizeof(long));
	printf("unsigned long long: %ld\n", sizeof(unsigned long long));
	printf("long long: %ld\n", sizeof(long long));
	printf("float：　%ld\n", sizeof(float));
	printf("double：　%ld\n", sizeof(double));
	
	return 0;
}
