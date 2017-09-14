#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

char shiftChar(char c, int key, int lower, int upper);

int * strToIntArray(string keyWord);

bool validInput(string str);

int main (int argc, string argv[])
{
    // program not exicuted with 2 arguments
    if (argc != 2)
    {
        printf("Improper number of command line arguements\n");
        return 1;
    }
    // get key word from comand line
    string keyWord = argv[1];
    int keyLen = strlen(keyWord);
    
    if (!validInput(keyWord))
    {
        printf("Invalid input. Input may only contain letters\n");
        return 1;
    }
    
    // convert key word into an int array
    int *key;
    key = strToIntArray(keyWord);
    // index for key array
    int k = 0;
    
    // get text to encrypt
    string plainText = GetString();
    int len = strlen(plainText);
    string cypherText = plainText;
    
    for (int i = 0; i < len; i++ )
    {
        // re set key index to 0 if it reaches the lenght of key word
        if (k >= keyLen)
        {
            k=0;
        }
        // check if char is lowercase
        if (islower(plainText[i]))
        {
            // ascii range for lower case letters 97 to 122
            cypherText[i] = shiftChar(cypherText[i], key[k++], 97 ,122);
        }
        // check if char is uppercase
        else if (isupper(plainText[i]))
        {
            // ascii 65 to 90
            cypherText[i] = shiftChar(cypherText[i], key[k++], 65, 90);
        }
    }
    
    
    
    printf("%s\n", cypherText);
    free(key); key = NULL;
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

int * strToIntArray(string keyWord)
{
    //
    string abc = "abcdefghijklmnopqrstuvwxyz";
    int len = strlen(keyWord);
    // initalize int array to return
    int *nums = malloc(sizeof(int) * len);
    // go through key word
    for(int i = 0; i < len; i++)
    {
        // compare to abc string
        for(int j = 0; j < 26; j++)
        {
            if( tolower(keyWord[i]) == abc[j] )
            {
                nums[i] = j;// use index as numerical representation of letter
            }
        }
    }
     
    return nums;
}

bool validInput(string str)
{
    // make sure string only contains letters
    int l = strlen(str);
    for (int i = 0; i < l; i++)
    {
        if ( !(isupper(str[i]) || islower(str[i]) ))
        {
            return false;
        }
    }
    return true;
}