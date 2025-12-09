#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "DynamicLists/list.h"

typedef char* string ;
typedef struct node
{
    string val ;
    struct node* next ;
}node;
typedef struct hashTable{
node* array[29] ;
int length  ;

} hashTable; 
int hashing(string word){
    unsigned int hash = 0 ; 
    while (*word)
    {
    hash = hash * 31 + *word ;
    word ++;
    }
    return hash ;
}
void insert(hashTable* ht,string word){
  int  hash = hashing(word) ;
  int index = hash % (*ht).length ;
  // we set the length of the hash table 29 
  insert(&ht->array[index],word,0) ;

}
bool find(hashTable ht,string word){
  int hash = hashing(word) ;
  int index = hash % ht.length ;
  
   return ifItExists(ht.array[index],word) ;
  

}
hashTable creatHashTable(int leng){
   // maximum length is 29 , this is not a database ,you should know that
    hashTable ht ;
    if(leng<= 29)
    ht.length = leng;
    else 
    ht.length = 29 ;

    for(int i = 0;i<ht.length;i++) ht.array[i] = NULL ; // we need to loop untill ht.length not leng in case the user inputed a wrong(over 29 or less than 0) length
    return ht ;
}









