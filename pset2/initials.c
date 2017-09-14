#include <string.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

void printUpper(char c)
{
    printf("%c", toupper(c) );
}

int main(void)
{
    // printf("What is your name? ");
    string name = GetString();
    int len = strlen(name);
    if (len >0)
    {
        // print the first letter 
        printUpper(name[0]);
        
    
        // start at 1 because code looks back a space
        for (int i = 1; i < len; i++) 
        {
            if (name[i-1] == ' ')
            {
                printUpper(name[i]);
            }
        
        }
        printf("\n");
    }
}