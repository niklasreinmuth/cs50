#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);
char encrypt(char c, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]))
            {
                printf("Usage: ./vigenere keyword\n");
                return 1;
            }
        }
        
        string plaintext = get_string("plaintext: ");
        string ciphertext = plaintext;
        
        for (int i = 0, n = strlen(plaintext), key_letter_count = 0; i < n; i++)
        {
            if (isalpha(plaintext[i]))
            {
                int overflow = key_letter_count % strlen(argv[1]);
                int shifted_k = shift(argv[1][overflow]);
                key_letter_count++;
                
                char encrypted_c = encrypt(plaintext[i], shifted_k);
                ciphertext[i] = encrypted_c;
            }
        }
        
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
}

int shift(char c)
{
    if (isupper(c))
    {
        c -= 'A';
    }
    else if (islower(c))
    {
        c -= 'a';
    }

    return c;
}

char encrypt(char c, int key)
{
    if (isupper(c))
    {
        c = (((c + key) % 'A') % 26) + 'A';
    }
    else if (islower(c))
    {
        c = (((c + key) % 'a') % 26) + 'a';
    }
    
    return c;
}
