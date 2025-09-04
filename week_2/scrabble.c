#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// C
void calculate_winner(string *both_words);
// U
string *user_prompt(void);

int main(void)
{
    // Two functions:
    // 1: Take the prompt from user
    string *both_words = user_prompt();

    // 2: Calculate points and choose the winner
    calculate_winner(both_words);
}

// Function to compare both words and choose the winner
void calculate_winner(string *both_words)
{
    // Declare variables for the values and length of both words
    const int N = 2;
    int length[N];
    int value_word[N];
    length[0] = strlen(both_words[0]);
    length[1] = strlen(both_words[1]);

    // For every word
    for (int i = 0; i < N; i++)
    {
        // Reseting to 0 points at the beginning of every word
        value_word[i] = 0;

        // Checking every character of the word
        for (int j = 0; j < length[i]; j++)
        {
            char letter = toupper(both_words[i][j]);

            switch (letter)
            {
                // 1 point: A, E, I, L, N, O, R, S, T, U;
                case 'A':
                case 'E':
                case 'I':
                case 'L':
                case 'N':
                case 'O':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                    value_word[i] += 1;
                    break;

                // 2 points: D, G;
                case 'D':
                case 'G':
                    value_word[i] += 2;
                    break;

                // 3 points: B, C, M, P;
                case 'B':
                case 'C':
                case 'M':
                case 'P':
                    value_word[i] += 3;
                    break;

                // 4 points: F, H, V, W, Y;
                case 'F':
                case 'H':
                case 'V':
                case 'W':
                case 'Y':
                    value_word[i] += 4;
                    break;

                // 5 points: K;
                case 'K':
                    value_word[i] += 5;
                    break;

                // 8 points: J, X;
                case 'J':
                case 'X':
                    value_word[i] += 8;
                    break;

                // 10 points: Q, Z;
                case 'Q':
                case 'Z':
                    value_word[i] += 10;
                    break;
            }
        }
    }

    // Choosing the winner [0] = First word/player, [1] = Second word/player
    if (value_word[0] > value_word[1])
    {
        printf("Player 1 wins!\n");
    }
    else if (value_word[0] < value_word[1])
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Function to get both words from the user and return a pointer (string* == char**)
// to the static array
string *user_prompt()
{
    // Saving input of user in this array, it's static so we won't lose the value after
    // the function ends
    static string both_inputs[2];
    both_inputs[0] = get_string("Player 1: ");
    both_inputs[1] = get_string("Player 2: ");
    return both_inputs;
}
