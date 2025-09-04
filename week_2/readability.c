#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// C
float *calculate_averages(string text);
// R
void readability_algorithm(float *averages);
// U
string user_prompt();

int main(void)
{
    // 1: Takes text 2: Calculates the averages 3: Chooses grade level
    readability_algorithm(calculate_averages(user_prompt()));
}

float *calculate_averages(string text)
{
    // Variables to take the count of letters, words, and sentences
    int letters_count = 0;
    int sentences_count = 0;
    int words_count = 1;

    // Going through every character
    for (int i = 0, text_length = strlen(text); i < text_length; i++)
    {

        // Checking if is a letters (new letter)
        if (isalpha(text[i]))
        {
            letters_count += 1;
        }

        // Checking if is a space (new word)
        else if (isspace(text[i]))
        {
            words_count += 1;
        }

        // Checking if is a punctuation (new sentence)
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences_count += 1;
        }
    }

    // Static array that saves both avarages to take it to the main function
    static float average[2];

    // Average letters per 100 words
    average[0] = 100.0 * letters_count / words_count;

    // Average sentences per 100 words
    average[1] = 100.0 * sentences_count / words_count;

    // Return the array with the averages of letters and sentences
    return average;
}

void readability_algorithm(float *averages)
{
    // Coleman-Liau formula to calculate the grade level using averages per 100 words
    // Average letters equals averages[0] and average sentences equals averages[1]
    int grade_result = round(0.0588 * averages[0] - 0.296 * averages[1] - 15.8);

    // Choosing the proper grade
    if (grade_result < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_result < 16)
    {
        printf("Grade %d\n", grade_result);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

// Getting the text input from the user
string user_prompt()
{
    string text = get_string("Text: ");
    return text;
}
