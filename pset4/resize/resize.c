/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4 || atoi(argv[1]) > 99)
    {
        fprintf(stderr, "Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // read resizing factor from command line 
    int factor = atoi(argv[1]);
    
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


    // I will probably need to change the meta data here
    // bfSize, biWidth, biHeight, biSizeImage, 
    bi.biWidth *= factor;
    bi.biHeight *= factor;
    
    // determine padding for lines
    int preResizePadding = (4 - (bi.biWidth/factor * sizeof(RGBTRIPLE)) % 4) % 4;
    int postResizePadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biSizeImage = ((sizeof(RGBTRIPLE)*bi.biWidth)+ postResizePadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);// am i doing this right?
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight/factor; i++)
    {
        // use an array of RGBTRIPLE to store scanlines
        RGBTRIPLE line[bi.biWidth];
        int index = 0;
        
        // iterate over pixels in scanline and put into array
        for (int j = 0; j < bi.biWidth/factor; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // put line of pixles into a more perminent location
            for (int p = 0; p < factor; p++)
            {
                line[index++] = triple;
            }
            
            
        }
        // skip over padding, if any
        fseek(inptr, preResizePadding, SEEK_CUR);
        
        // repeat row of pixles factor times
        for (int k = 0; k < factor; k++)
        {
            // iterate through line of pixles 
            for (int j = 0; j < bi.biWidth; j++)
            {
                // write RGB triple to outfile n times
                fwrite(&line[j], sizeof(RGBTRIPLE), 1, outptr);
            }
            // add new padding  
            for (int h = 0; h < postResizePadding; h++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
