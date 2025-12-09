#ifndef HASH_H
#define HASH_H

#include <stdbool.h>
#include "DynamicLists/list.h"  // for node definition and list functions

typedef char* string;

// Node struct (if needed outside, otherwise you can remove)
typedef struct node {
    string val;
    struct node* next;
} node;

// Hash table struct
typedef struct hashTable {
    node* array[29];
    int length;
} hashTable;

// Hash function
int hashing(string word);

// Hash table functions
void insertValHash(hashTable* ht, string word);
bool find(hashTable ht, string word);
hashTable createHashTable(int leng);
string deleteValHash(hashTable* ht,string word) ;

#endif // HASH_H
