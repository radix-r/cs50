#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    printf("How much chage is owed? ");
   
    float change = GetFloat();
   
    while(change < 0.0)
    {
        printf("Enter a positive value\n");
        printf("Retry: ");
        change = GetFloat();
    }
    
    // convert from dollars to cents 
    change = change * 100;
    change = round(change);
    // cast to int to avoid errors
    int cents = (int) change; // 100 = $1
    // remove whole dollars 
    // cents = cents % 100;
    
    int coins = 0;
    
    while (cents >= 25)// quarters 
    {
        cents-= 25;
        coins++;
    }
    while(cents >= 10)// dimes
    {
        cents -= 10;
        coins++;
    }
    while(cents >= 5)// nickles
    {
        cents-= 5;
        coins++;
    }
    while(cents >=1)// pennies
    {
        cents -= 1;
        coins++;
    }
    printf("%i\n", coins);
}