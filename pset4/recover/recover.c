/*
Ross Wagner
recovers "deleted" JPEG files from a memory card

assignment
http://docs.cs50.net/2017/x/psets/4/pset4.html
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Proper usage: ./recover infile\n");
        return 1;
    }
    // initalize vars
    char* infile = argv[1];
    char outfile[7];
    int counter = 0;
    unsigned char* buffer = malloc(512);
    FILE *outP = NULL;
    
    FILE *inP = fopen(infile, "r");
    
    if (inP == NULL)
    {
        fprintf(stderr,"Infile opening failed");
        return 2;
    }
    
    // read through infile 512 bytes at a time 
    while (fread(buffer, 1, 512, inP) == 512) 
    {
        // if first 4 bytes 0xff 0xd8 0xff 0xe[0-f]start writing to new jpeg
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)//i dont understand this part
        {
            
            // name the outfile
            //char outfile[7];
            sprintf(outfile,"%03i.jpg", counter);
            
            //close pevious jpeg files (if any)
            if(outP != NULL)
            {
                fclose(outP);
            }
        
            // open the new outfile
            outP = fopen(outfile, "w");
            counter++;
        }
        
        // write to current outfile
        if (outP != NULL)
            fwrite(buffer, 1, 512, outP);
        
    }
    
    free(buffer);
    fclose(inP);
    if (outP != NULL)
        fclose(outP);
    
    
    return 0;
}