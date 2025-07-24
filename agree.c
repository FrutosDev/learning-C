#include <stdio.h>

int main(void)
{
    char answer;
    printf("Do you agree? ");
    scanf("%c", &answer);

    if (answer == 'y' || answer == 'Y') // When comparing single char values '' are needed instead of ""
    {
        printf("You agreed!\n");
    }
    else if (answer == 'n' || answer == 'N')
    {
        printf("You didn't agree!\n");
    }
    else
    {
        printf("Well, that's a weird answer...\n");
    }
}

