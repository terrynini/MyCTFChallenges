#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <string.h>

void verify_1();
void verify_2();
void verify_3();
void verify_4();
void verify_5();

void xor(char*a , char*b);
void check(char* input);

struct Check
{
    void (*func)() ;
    char* input;
    int offset;
    int chr_idx;
    int check_len;
    int verify[2];
} checker;

#include "./flag.h"
#define DATA_LEN 70

void __attribute__ ((constructor)) anti_debug() 
{ 
    puts("Welcom to the moon");
    puts("We need you to help us to build a storage for Pi"); 
    puts("Are you familiar with the O(1) algorithm for fibonacci sequence ??");
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) 
    {
        exit(0);
    }
}

int main()
{
    char input[DATA_LEN+1];
    char flag[DATA_LEN+1] = {69, 74, 93, 85, 100, 69, 75, 88, 75, 20, 34, 8, 69, 1, 34, 115, 48, 119, 6, 10, 70, 123, 24, 14, 80, 99, 21, 52, 89, 109, 83, 102, 74, 118, 84, 29, 106, 32, 109, 103, 48, 100, 124, 85, 28, 3, 40, 20, 81, 94, 33, 18, 17, 15, 55, 3, 91, 61, 94, 57, 81, 126, 29, 90, 87, 11, 123, 70, 20, 103};

    for(int i = 0 ; i < 1000 ; i ++)
    {
        printf("What is the %d key ?",i);
        memset(input, 0, DATA_LEN);
        scanf("%70s", input);
        check(input);
        xor(flag,input); 
    }
    printf("We need you !! Contact our HR, and the flag is %s", flag);
}

int idx = 0;

void check(char* input)
{
    int i = 0;
    while( i < 70)
    {
        checker.input = input;
        checker.chr_idx = data[idx].chr_idx;
        checker.check_len = data[idx].check_len;
        checker.verify[0] = data[idx].verify[0];
        checker.verify[1] = data[idx].verify[1];
        checker.offset = data[idx].offset;
        checker.func = data[idx].func+checker.offset;
        checker.func();
        idx++;
        i+= checker.check_len;
    }
}

void xor(char*a , char*b)
{
    for(int i = 0 ; i < DATA_LEN ; i++)
        a[i] ^= b[i];
}

void verify_1()
{
    for(int i = 0 ; i < checker.check_len ; i++)
    {
        if( checker.verify[i] != checker.input[i+checker.chr_idx]*5566 )
            exit(0);
    }
}

void verify_2()
{
    int v5;
    for(int i = 0 ; i < checker.check_len ; i++)
    {
        v5 = 0;
        for(int j = 0 ; j < checker.input[i+checker.chr_idx] ; j++)
        {
            if( j & 1)
                v5 += 1;
            else
                v5 += 3;
        }
        if( checker.verify[i] != v5)
            exit(0);
    }
}

void verify_3()
{
    for(int i = 0 ; i < checker.check_len ; i++)
        if( checker.verify[i] != (checker.input[i+checker.chr_idx]^5566) )
            exit(0);
}

void verify_4()
{
    unsigned int v5;
    for(int i = 0 ; i < checker.check_len ; i++)
    {
        v5 = 0xdeadbeef;
        for(int j = 0 ; j < checker.input[i+checker.chr_idx] ; j++)
        {
            if (j &1)
                v5 -= 0x5566;
        }

        if( checker.verify[i] != v5 )
            exit(0);
    }
}

void verify_5()
{
    unsigned int v5;
    for(int i = 0 ; i < checker.check_len ; i++)
    {
        unsigned int pp = 0 , p = 1;
        for(int j = 0 ; j < checker.input[i+checker.chr_idx] ; j++)
        {
            v5 = pp+p;
            pp = p;
            p = v5;
        }
        if( checker.verify[i] != v5)
            exit(0);
    }
}
