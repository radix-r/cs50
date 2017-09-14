#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("minutes: ");
    int min = GetInt();
    
    int bottlesPerMin = 12;
    printf("bottles: %i\n", bottlesPerMin * min); 
    
}