#include <stdio.h>

typedef unsigned long   unit64;
typedef unsigned int    unit32;
typedef unsigned short  unit16;
typedef unsigned char   unit8;

struct five_or_eight
{
    unit8   ch;
    unit32  number;
};

struct student
{
    char    name[7];
    char    x[6];
    unit32  id;
};

struct test
{
    unit8   three_unit8[3];
    unit16  three_unit16[3];
    unit32  one_unit32;
    unit64  one_unit64;
    struct five_or_eight five;
};

struct inverse
{
    unit8   three_unit8[3];
    unit16  three_unit16[3];
    unit32  one_unit32;
    unit64  one_unit64;
    struct five_or_eight five;
}__attribute__((packed, aligned(1)));

int main()
{

    void * ptr;

    printf("length of unsigned long: %ld\n", sizeof(unit64));
    printf("length of unsigned int: %ld\n", sizeof(unit32));
    printf("length of unsigned short: %ld\n", sizeof(unit16));
    printf("length of unsigned char: %ld\n", sizeof(unit8));

    printf("length of struct student: %ld\n", sizeof(struct student));
    printf("length of struct test: %ld\n", sizeof(struct test));
    printf("length of struct inverse: %ld\n", sizeof(struct inverse));

    printf("lenght of pointer: %ld\n", sizeof(ptr));

    return 0;
}
