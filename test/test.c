#include <stdio.h>

int main()
{
    long unsigned int a;
    size_t b;

    printf("Hello world!\n");
    printf("length long unsigned int: %ld\n", sizeof(a));
    printf("length of size_t: %ld\n", sizeof(b));
    return 0;
}
