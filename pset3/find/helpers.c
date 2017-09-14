/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

void swap(int values[], int pos1, int pos2);
bool binarySearch(int value, int values[], int min, int max);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // binary search
    return binarySearch(value, values, 0, n);
}

/**
 * recursive binary search implementation
 */
bool binarySearch(int value, int values[], int min, int max)
{
    if (max < min)
    { 
        return false;
    }
    // find mid point
    int mid = (max + min) / 2;
    // guess too small. use larger half   
    if (values[mid] < value)
    { 
        return binarySearch(value, values, mid+1, max);
    }
    // guess too large. use smaller half
    else if (values[mid] > value)
    { 
        return binarySearch(value, values, min, mid-1);
    }
    // must be equal
    else
    { 
        return true;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // selection sort
    // index of the start of the unsorted portion
    for (int p = 0; p < n; p++)
    {
        //
        int lowest = p;
        for(int i = p; i < n; i++)
        {
            // find the lowest value
            if (values[i] < values[lowest])
            { lowest = i; }
        }
        //swap with values[p]
        swap(values, p, lowest);
    }
}

/**
 * swaps the position of two elements in an array
 */
void swap(int values[], int pos1, int pos2)
{
    int coppy = values[pos1];
    values[pos1] = values[pos2];
    values[pos2] = coppy;
}
