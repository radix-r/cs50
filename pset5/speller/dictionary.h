/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// number of elements in trie pointer array
#define NUMELEM 27

//
typedef struct _trie
{
    bool isWord; // true if path is a word false if it isnt
    struct _trie* paths[NUMELEM]; // pointer spot for each letter in alphabet
}
tnode; // short for trie node


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * free all nodes that node points to then frees node
 */
bool del(tnode* node);

/**
 * Converts char to its position in alphabet
 */
int charToInt(char letter); // this is my addition. may need to remove
 
/**
 * Creates new trie node
 */
tnode* create(void);

#endif // DICTIONARY_H
