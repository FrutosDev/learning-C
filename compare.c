#include <stdio.h>

int main(void)
{
    int x, y;

    printf("Please enter the value of x:");
    scanf("%d", &x);

    printf("Please enter the value of y:");
    scanf("%d", &y);
    
    if (x > y)
    {
        printf("x is bigger than y.\n");
    }
    else if (x < y)
    {
        printf("x is less than y.\n");
    }
    else
    {
        printf("Is the same value I guess?\n");
    }
}