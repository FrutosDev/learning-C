#include <cs50.h>
#include <math.h>
#include <stdio.h>
// The idea of taking the math library comes from the cs50 documentation

// E
int extract_digits(long long card_number, int length_number);
int extract_length_number(long long card_number);
// G
string get_card_id(long long card_number, int length_number);
// P
long long prompt_user(void);

int main(void)
{

    long long card_number = prompt_user();

    int length_number = extract_length_number(card_number);

    int final_result = extract_digits(card_number, length_number);

    if (final_result % 10 == 0)
    {
        string card_type = get_card_id(card_number, length_number);
        printf("%s\n", card_type);
    }
    else
    {
        printf("INVALID\n");
    }
}

int extract_digits(long long card_number, int length_number)
{
    // Variables used for the loop and/or the math operations
    long long x = 10;
    long long previous_digit = 0;
    long long digit = 0;
    long long j;

    // Variables used to calculate the sum of the "even" digits (every other digit)
    int result_multiplication = 0;
    int result_addition = 0;

    for (int i = 0; i < length_number; i++)
    {
        previous_digit = digit;
        long long temporary_digit = card_number % x;
        digit = temporary_digit - previous_digit;
        x *= 10;
        j = pow(10, i);
        long long final_digit = digit / j;
        int digit_check = i + 1;

        // Conditional used to separate every other digit and calculate the sums/multiplication
        if (digit_check % 2 == 0)
        {
            int multiplication = final_digit * 2;
            if (final_digit >= 5)
            {
                switch (final_digit)
                {
                    case 5:
                        multiplication = 1; // 10 = 1 + 0
                        break;
                    case 6:
                        multiplication = 3; // 12 = 1 + 2
                        break;
                    case 7:
                        multiplication = 5; // 14 = 1 + 4
                        break;
                    case 8:
                        multiplication = 7; // 16 = 1 + 6
                        break;
                    case 9:
                        multiplication = 9; // 18 = 1 + 8
                        break;
                }
                result_multiplication = result_multiplication + multiplication;
            }
            else if (final_digit > 0 && final_digit < 5)
            {
                result_multiplication = result_multiplication + multiplication;
            }
        }
        else
        {
            result_addition = result_addition + final_digit;
        }
    }

    // The result to check if the card follows Luhn's algorithm
    int final_result = result_multiplication + result_addition;
    return final_result;
}

int extract_length_number(long long card_number)
{
    int length_number = 0;
    long long check_every_digit = 0;

    // Taking the length of the number by dividing by 10 the card number and checking the reminder
    for (long long i = 10; card_number > check_every_digit; i *= 10)
    {
        check_every_digit = card_number % i;
        length_number++;
    }
    return length_number;
}

string get_card_id(long long card_number, int length_number)
{
    // Identifying the card by length and by the id (id = digits at the beginning of the card)
    int card_id = 0;
    if (length_number == 16)
    {
        card_id = card_number / pow(10, 14);
        if (card_id > 39 && card_id < 50)
        {
            return "VISA";
        }
        else if (card_id == 55 || card_id == 54 || card_id == 53 || card_id == 52 || card_id == 51)
        {
            return "MASTERCARD";
        }
        else
        {
            return "INVALID";
        }
    }
    else if (length_number == 15)
    {
        card_id = card_number / pow(10, 13);
        if (card_id == 34 || card_id == 37)
        {
            return "AMEX";
        }
        else
        {
            return "INVALID";
        }
    }
    else if (length_number == 13)
    {
        card_id = card_number / pow(10, 11);
        if (card_id > 39 && card_id < 50)
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }
    return "INVALID";
}

long long prompt_user(void)
{
    long long card_number;
    do
    {
        long long number = get_long("Insert your card number: ");
        card_number = number;
    }
    while (card_number <= 0 || card_number > 9999999999999999);
    return card_number;
}
