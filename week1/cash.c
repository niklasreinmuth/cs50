#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_change(string prompt);
int calculate_coins(int amount);

int main(void)
{
    int dollars = get_change("How much change? ");
    int coins = calculate_coins(dollars);
    printf("%i\n", coins);
}

int get_change(string prompt)
{
    float change;
    do
    {
        change = get_float("%s", prompt);    
    }
    while (change <= 0);
        
    int n = round(change * 100);
    
    return n;
}

int calculate_coins(int amount)
{
    int coins = 0;
    
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    
    if(amount / quarter > 0)
    {
        coins += amount / quarter;
        amount = amount % quarter;
    }
    
    if(amount / dime > 0)
    {
        coins += amount / dime;
        amount = amount % dime;
    }
    
    if(amount / nickel > 0)
    {
        coins += amount / nickel;
        amount = amount % nickel;
    }
    
    if(amount / penny > 0)
    {
        coins += amount / penny;
        amount = amount % penny;
    }
    
    return coins;
}
