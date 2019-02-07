#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <crypt.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    else
    {
        // Store first two chars of argv[1] in salt.
        char salt[3];
        salt[0] = argv[1][0];
        salt[1] = argv[1][1];
        
        // Store salt and chars 3 to 13 of argv[1] in argv_hashed.
        // This is the actual hash to compare the brute-force to later.
        // Will look something like this: 50cI2vYkF0YU2 (50 = salt).
        char argv_hashed[14];
        argv_hashed[0] = salt[0];
        argv_hashed[1] = salt[1];
        for (int i = 2, n = 13; i < n; i++)
        {
            argv_hashed[i] = argv[1][i];
        }
        
        // Optimized by letter frequency
        string library = "\0EeTtAaOoIiNnSsRrHhLlDdCcUuMmFfPpGgWwYyBbVvKkXxJjQqZz";
        int library_length = 53;
        char password[6] = {'\0'};
        
        // For loops start with comparing a single char password since our library
        // starts with '\0' -> which 'ends' a string. Thus, the last loop (our
        // first char of the password) starts counting at 1 to skip the '\0'.
        //
        // Essentially maps out to this:
        // \0 \0 \0 \0  x
        // \0 \0 \0  x  x
        // \0 \0  x  x  x
        // \0  x  x  x  x
        //  x  x  x  x  x
        for (int i = 0; i < library_length; i++)
        {
            for (int j = 0; j < library_length; j++)
            {
                for (int k = 0; k < library_length; k++)
                {
                    for (int l = 0; l < library_length; l++)
                    {
                        for (int m = 1; m < library_length; m++)
                        {
                            password[0] = library[m];
                            password[1] = library[l];
                            password[2] = library[k];
                            password[3] = library[j];
                            password[4] = library[i];
                            
                            // crypt() the brute-forced password with the determined salt
                            // and check if they're equal to the given argv[1] by the user.
                            if (strcmp(crypt(password, salt), argv_hashed) == 0)
                            {
                                printf("%s\n", password);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
  
        return 0;
    }
}
