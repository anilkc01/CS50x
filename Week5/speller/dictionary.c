// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    // Convert input  to lowercase
    char lowercase_word[LENGTH + 1];
    for (int i = 0; i < strlen(word); i++)
    {
        if(word[i] >= 'A' && word[i] <= 'Z'){
            lowercase_word[i] = tolower(word[i]);
        }
        else{
            lowercase_word[i] = word[i];
        }

    }
    lowercase_word[strlen(word)] = '\0';

    // generaate hash value for the word
    unsigned int index = hash(lowercase_word);



    // Traverse the linked list at the index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Compare the word with the current node's word
        if (strcasecmp(cursor->word, lowercase_word) == 0)
        {
            // if found in dictionary then return true
            return true;
        }
        cursor = cursor->next;
    }

    // if thw word is not found
    return false;
}

// hash word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    // Ensure the result is within the range [0, N-1]
    return hash % N;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }


    char buffer[LENGTH + 1];


    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Convert to lowercase
        for (int i = 0; buffer[i]; i++)
        {
                 buffer[i] = tolower(buffer[i]);
        }

        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        //cpy value from buffer to new node
        strcpy(new_node->word, buffer);
        new_node->next = NULL;

        // Calculate the hash value for the word
        unsigned int index = hash(buffer);

        // Insert the word into the hash table
        if (table[index] == NULL)   //if place is free
        {
            table[index] = new_node;
        }
        else     //if place is not free, add to the begining of liked list
        {
            new_node->next = table[index];
            table[index] = new_node;
        }
    }


    fclose(file);

    return true;
}



// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
   int word_count = 0;

    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            word_count++;
            cursor = cursor->next;
        }
    }

    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
     for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
