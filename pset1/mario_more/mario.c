#include <stdio.h>
#include <cs50.h>

int get_height(string prompt);

int main(void)
{
    int height = get_height("Height: ");
    
    for (int i = 0; i < height; i++)
    {
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }
        
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        
        printf("  ");
        
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}

int get_height(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    
    return n;
}
