// *** Headers Files *** //
// C
#include <cs50.h>
#include <ctype.h>
// S
#include <stdio.h>
#include <string.h>

// *** Functions *** //
// E
int encipher_text(string argv, string plaintext);
// K
int key_validation(string argv);

// *** Global Variables *** //
// S
const char standard_alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                                    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                                    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main(int argc, string argv[])
{
    // Checking if the user prompts less or more than two arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if the key is 26 characters long
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Validate if the characters is repeated or is something different than a letter
    else if (key_validation(argv[1]) == 0)
    {
        encipher_text(argv[1], get_string("plaintext:  "));
    }

    // If validation returns anything but 0, there was an error
    else
    {
        return 1;
    }
}

int encipher_text(string argv, string plaintext)
{
    int length_plaintext = strlen(plaintext);
    char enciphered_text[length_plaintext];

    // Going through the whole plaintext
    for (int i = 0; i < length_plaintext; i++)
    {
        // If is a letter is being enciphered
        if (isalpha(plaintext[i]))
        {
            // Looking what is the corresponding enciphered letter
            int letter_searcher = 0;
            while (toupper(plaintext[i]) != standard_alphabet[letter_searcher])
            {
                letter_searcher++;
            }

            // Checking if is upper case or lower case and choosing the corresponding letter
            if (isupper(plaintext[i]))
            {
                enciphered_text[i] = argv[letter_searcher];
            }
            else
            {
                enciphered_text[i] = tolower(argv[letter_searcher]);
            }
        }

        // Not a letter, so it remains the same
        else
        {
            enciphered_text[i] = plaintext[i];
        }
    }

    // Printing the enciphered text
    printf("ciphertext: ");
    for (int j = 0; j < length_plaintext; j++)
    {
        printf("%c", enciphered_text[j]);
    }
    printf("\n");
    return 0;
}

int key_validation(string argv)
{
    // Going through every character of the key
    for (int i = 0; i < 26; i++)
    {
        // Validate if the character is a letter
        if (isalpha(argv[i]))
        {
            // Checking if the letter is repeated
            int repeated_letter = 0;
            for (int j = 0; j < 26; j++)
            {
                // Comparing the character with eachothers
                if (toupper(argv[i]) == toupper(argv[j]))
                {
                    repeated_letter++;
                }
            }

            // More than one means is not a unique letter
            if (repeated_letter > 1)
            {
                printf("Every letter of the key must be unique.\n");
                return 1;
            }
        }

        // The character is not a letter
        else
        {
            printf("The key must contain only letters.\n");
            return 1;
        }

        // Normalizing the key to uppercase
        argv[i] = toupper(argv[i]);
    }
    return 0;
}
