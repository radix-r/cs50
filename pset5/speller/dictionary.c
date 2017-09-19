/**
 * Author: Ross Wagner
 * Implements a dictionary's functionality.
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"


// array used for char to int conversion
char *abcd = {"abcdefghijklmnopqrstuvwxyz'"};




// pointer to the start of the trie that holds the dictionary
tnode* base = NULL;

// number of words currently in dictionary
unsigned int numWords;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // debug
    //fprintf(stdout, "|%s|", word);
    
    // follow path through trie data structure
    
    int i, charVal, wordLen = strlen(word);
    // set current ptr to start of trie
    tnode* current = base;
    
    for (i=0; i < wordLen; i++)
    {
        
        
        char lower = tolower(word[i]);
        // find value of current char
        charVal = charToInt(lower);
        // go to that path
        current = current->paths[charVal];
        
        // confirm pathway exits
        if(current == NULL)
        {
            return false;
        }
        
        // path followed. is path consitered a word?
        else if (i == wordLen -1)
        {
            //debug
            //fprintf(stdout, " %c ", word[i]);
            return current->isWord;
        }
        
    }
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    // load txt file into data structure
    
    // open txt file
    FILE* in = fopen(dictionary, "r");
    
    // confirm opening
    if (in == NULL)
    {
        fprintf(stderr, "Failed to open dictionary");
        return false;
    }
    
    // where ther word that will be read in will go
    char inWord[LENGTH];
    
    // create base node of dictionary
    base = create();// make this global?
    
    // index for loop
    int i;
    
    // pointer to current location in trie
    tnode* current; 
    
    // get words form file
    while (fscanf(in, "%s", inWord) != EOF)
    {
        // debug
        //printf("*%s*", inWord);
        
    
        // reset current ptr to point to head of data structure
        current = base;
        
        // length of word read in by fgets
        int wordLen = strlen(inWord);
        
        // put word into data structure
        for(i=0; i < wordLen; i++)
        {
            // converts char to ascii value
            int ascii = inWord[i];
            
            // skips if newline 
            if (ascii != 10)
            {
            
                // convert current char to lower case
                char lower = tolower(inWord[i]);
                
                // convert current character to an int. a-z 0-25
                int charVal = charToInt(lower);
                
                // confirm valid value
                if (charVal == -1)
                {
                    unload();
                    fclose(in);
                    return false;
                }
                
                // only create a new node of path dosnt exist
                if (current->paths[charVal] == NULL)
                {
                
                    // create a new trie node
                    tnode *newNode = create();
                    // make sure malloc didnt fail
                    if (newNode == NULL)
                    {
                        unload();
                        fclose(in);
                        return false;
                    }
                    
                    // open path to another node
                    current->paths[charVal] = newNode;
                }
                // move current ptr to next node in trie
                current = current->paths[charVal];
                
                // debug
                //fprintf(stdout,"->%c", inWord[i]);
                
            }
            
            // if end of word, set current node's value to true
            if (i == wordLen-1 )
            {
                // debug---------------------------------------------
                // fprintf(stdout," |%c| ", inWord[i]);
                current->isWord = true;
                // perhaps increment a counter representing the number of words in data stucture?
                numWords++;
                //debug
                //printf(" %d ",numWords);
                
            }
        
        
        }
        
        
    }
    
     // return true if end of file reached. else dictionary not read. return false
    bool fin;
    fin = feof(in);
    fclose(in);
    return fin;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    // am i cheating here?
    return numWords;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    int i;
    
    // free all nodes that base points to
    for (i = 0; i < NUMELEM; i++)
    {
        if (base->paths[i] != NULL)
        {
            // if node deletion fails return false
            if (!del(base->paths[i]))
            {
                return false;
            }
        }
    }
    
    free(base);
    
    return true;
}

/**
 * free all nodes that node points to then frees node
 */
bool del(tnode* node)
{
    int j;
    // delete/free all nodes node points to
    for(j = 0; j < NUMELEM; j++)
    {
        if (node->paths[j] != NULL)
        {
            // if deletion fails return false
            if (!del(node->paths[j]))
            {
                return false;
            }
        }
    }
    
    free(node);
    
    // node sucessfully freed
    return true;
    
}


/**
 * Converts char to its position in alphabet
 */
 int charToInt(char letter)
 {
     int i;
     // look through array containing valid characters 
     for (i = 0; i < strlen(abcd); i++)
     {
         if (letter == abcd[i])
            return i;
     }
     fprintf(stderr, "Unexpected character for char to int coversion: %c\n", letter);
     return -1;
 }
 
 /**
 * Creates new trie node
 */
 tnode* create(void)
 {
     // allocate memory and point to it
     tnode* node = malloc(sizeof(tnode));
     
     // set isWord field
     node->isWord = false;
     
     int i;// numOfElements;
     // find number of elements
     //numOfElements = sizeof(node->paths) / sizeof(node->paths[0]);
     // intitalize paths array to all null pointers
     for  (i = 0; i > NUMELEM; i++)
     {
         node->paths[i] = NULL;
     }
     
     // return pointer to the new node 
     return node;
 }
