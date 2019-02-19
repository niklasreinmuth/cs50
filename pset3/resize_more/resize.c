// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    float resize_factor = atof(argv[1]);
    if (resize_factor < 0.0 || resize_factor > 100.0)
    {
        fprintf(stderr, "Error: f has to be greater than 0.0 and less than or equal to 100.0\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // new outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER out_bf;
    out_bf = bf;

    // new outfile's BITMAPINFOHEADER
    BITMAPINFOHEADER out_bi;
    out_bi = bi;

    // determine new width and height
    out_bi.biHeight = round(bi.biHeight * resize_factor);
    out_bi.biWidth = round(bi.biWidth * resize_factor);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine additionally needed header information
    out_bi.biSizeImage = ((sizeof(RGBTRIPLE) * out_bi.biWidth) + new_padding) * abs(out_bi.biHeight);
    out_bf.bfSize = out_bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine ratio
    double height_ratio = (double) bi.biHeight / (double) out_bi.biHeight;
    double width_ratio = (double) bi.biWidth / (double) out_bi.biWidth;

    // allocate memory to store one scanline
    RGBTRIPLE scanline[bi.biWidth * sizeof(RGBTRIPLE)];
    int cached_scanline = -1;

    // for all rows in the new image
    for (int i = 0, biHeight = abs(out_bi.biHeight); i < biHeight; i++)
    {
        // compute the Y coordinate of the corresponding row in the old image
        int row = i * height_ratio;

        // read the corresponding scanline from the old image unless it's cached
        if (cached_scanline != row)
        {
            fseek(inptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * row), SEEK_SET);
            fread(scanline, sizeof(RGBTRIPLE), bi.biWidth, inptr);
            cached_scanline = row;
        }

        // for all columns in the new image
        for (int j = 0; j < out_bi.biWidth; j++)
        {
            // compute the X coordinate of the corresponding column in the old image
            int column = j * width_ratio;
            fwrite(&scanline[column], sizeof(RGBTRIPLE), 1, outptr);
        }

        // write new padding
        for (int j = 0; j < new_padding; j++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
