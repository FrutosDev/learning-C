#include <stdio.h>

int user_prompt(void);
void generate_piramid(int height);

int main(void)
{
    int height = user_prompt();
    generate_piramid(height);
}

int user_prompt(void)
{
    int rows;
    do
    {
        printf("Enter number of rows (1-8): ");
        scanf("%i", &rows);
    }
    while(rows < 0 || rows > 8);
    return rows;
}


void generate_piramid(int height)
{
    // Print each row
    for(int i = 0; i < height; i++)
    {
        // Print left spaces
        for(int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        // Print left hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        // Print gap
        printf("  ");
        
        // Print right hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        // New line
        printf("\n");
    }
}