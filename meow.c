#include <stdio.h>

int get_possitive_int(void); // int means it's returning an output, and void no input.
void meow(int n); // void means it's not taking an output, and int n means is taking an input.

int main(void)
{
    int times = get_possitive_int();
    meow(times);
}

int get_possitive_int(void)
{
    int n;
    do
    {
        printf("Enter a number: ");
        scanf("%d", &n);
    }
    while (n < 1);
    return n;
}

void meow(int n)
{
    for(int i = 0; i < n; i++) //If possible, always start counting from 0 in computer science
    {
        printf("meow!\n");
    }
}