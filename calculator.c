#include <stdio.h>

int main(void)
{
    int x ,y;
    
    printf("Enter x value:");
    scanf("%i", &x);

    printf("Enter y value:");
    scanf("%i", &y);

    printf("%.5f\n", (float) x / y);

}