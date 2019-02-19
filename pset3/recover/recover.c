#include <stdio.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // open mem card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fclose(file);
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // create temp out file
    FILE *img = NULL;

    // create buffer storage
    unsigned char buffer[512];
    char filename[8];

    // init filename counter
    int counter = 0;

    // read file 512 bytes at a time and store them
    while (fread(buffer, sizeof(buffer), 1, file) == 1)
    {
        // if first four bytes are jpeg signature bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close jpeg so we can read the next one
            if (img)
            {
                fclose(img);
            }

            // set filename and open image
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }

        // write image
        if (img)
        {
            fwrite(&buffer, sizeof(buffer), 1, img);
        }
    }

    fclose(img);
    fclose(file);
}
