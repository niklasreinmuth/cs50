#include <stdio.h>
#include <cs50.h>

long get_credit_card(string prompt);
int get_card_length(long card_number);
string validate_credit_card(long card_number);

int main(void)
{
    long card_number = get_credit_card("Number: ");
    int card_length = get_card_length(card_number);
    string status = validate_credit_card(card_number);
    printf("%s\n", status);
}

long get_credit_card(string prompt)
{
    long card_number;
    do
    {
        card_number = get_long("%s", prompt);
    }
    while (card_number < 0);
    
    return card_number;
}
    
int get_card_length(long card_number)
{
    int length = 0;
    while (card_number > 0)
    {
        card_number /= 10;
        length++;
    }
    
    return length;
}

string validate_credit_card(long card_number)
{
    long length = get_card_length(card_number);
    string card_type = "INVALID";
    int checksum = 0;
    
    // isolate every other rightmost digit and add to checksum.
    for (long i = 1; i <= length * 100000000000000; i *= 100)
    {
        int digit = (card_number / i % 10);
        checksum += digit;
    }    

    // isolate every other (other) rightmost digit, double it and add 
    // those to the checksum. if the doubled sum exceeds 10 however, 
    // split the digits and add those to checksum instead.
    for (long j = 10; j <= length * 1000000000000000; j *= 100)
    {
        int digit = (card_number / j % 10) * 2;
        checksum += (digit % 10) + (digit / 10);
    }
    
    if (checksum % 10 == 0)
    {
        if (length == 16)
        {
            int mc = card_number / 100000000000000;
            if (mc == 51 || mc == 52 || mc == 53 || mc == 54 || mc == 55)
            {
                card_type = "MASTERCARD";
            }
            else if (card_number / 1000000000000000 == 4)
            {
                card_type = "VISA";
            }        
        }
        
        if (length == 15)
        {
            int amex = card_number / 10000000000000;
            if (amex == 34 || amex == 37)
            {
                card_type = "AMEX";
            }
        }
        
        if (length == 13)
        {
            if (card_number / 1000000000000 == 4)
            {
                card_type = "VISA";
            }
        }
    }
    
    return card_type;
}
