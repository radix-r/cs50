#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Height: ");
    
    int height = GetInt();
    while ((height >= 23) ||(height < 0))
    {
        printf("Please enter a positive int that is less than 23\n");
        printf("Retry: ");
        height = GetInt();
    }
    
    int spaces = height - 1;
    int sharps = 2;
    
    for(int i = height; i > 0; i--)
    {
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < sharps; k++)
        {
            printf("#");
        }
        printf("\n");
        spaces--;
        sharps++;
    }
}