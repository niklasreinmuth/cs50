#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string encrypt(string plaintext, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key;
        
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
            else
            {
                key = atoi(argv[1]);
            }
        }

        string plaintext = get_string("plaintext: ");
        string ciphertext = encrypt(plaintext, key);
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
}

string encrypt(string plaintext, int key)
{
    string ciphertext = plaintext;
    
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];
        
        if (isupper(c))
        {
            c = (((c - 65 + key) % 26) + 65);
        }
        else if (islower(c))
        {
            c = (((c - 97 + key) % 26) + 97);
        }
        
        ciphertext[i] = c;
    }
    
    return ciphertext;
}
