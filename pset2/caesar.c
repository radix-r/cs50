#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char shiftChar(char c, int key, int lower, int upper);


int main (int argc, string argv[])
{
    // program exicuted with not 2 arguments
    if (argc != 2)
    {
        printf("Improper number of command line arguements\n");
        return 1;
    }
    // atoi part of stdio that converts a string to an int
    int key = atoi(argv[1]);
    
    string plainText = GetString();
    int len = strlen(plainText);
    string cypherText = plainText;
    
    for (int i = 0; i < len; i++ )
    {
        
        // check if char is lowercase
        if (islower(plainText[i]))
        {
            // ascii range for lower case letters 97 to 122
            cypherText[i] = shiftChar(cypherText[i], key, 97 ,122);
        }
        // check if char is uppercase
        else if (isupper(plainText[i]))
        {
            // ascii 65 to 90
            cypherText[i] = shiftChar(cypherText[i], key, 65, 90);
        }
    }
    
    
    
    printf("%s\n", cypherText);
    return 0;
}


char shiftChar(char c, int shift, int lower, int upper)
{
    
    int range = upper - lower;
    // convert char to ascii value
    int ascii = (int)c;
    // apply shift
    ascii += shift;
    
    if (ascii > upper)// loop around if to large
    {
        ascii = ((ascii - upper) % (range+1)) + lower-1;
    }
    else if (ascii < lower)// loop around, to small
    {
        ascii = 1+upper - ((lower - ascii) % (range+1));
    }
    // convert back to char
    char shifted = (char) ascii;
    return shifted; 
}