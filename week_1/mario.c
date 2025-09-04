#include <stdio.h>

void print_row(int n);

int main(void)
{
    //Const means constant so that the value of that variable can't be changed.
    const int n = 3;

    for (int i = 0; i < n; i++)
    {
        print_row(n);
    }
}

void print_row(int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}