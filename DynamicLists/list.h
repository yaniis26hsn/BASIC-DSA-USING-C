#ifndef LIST_H
#define LIST_H
#include <stdbool.h> 
typedef char* string ;
typedef struct node
{
    string val ;
    struct node* next ;
}node;
node* createNode(string data) ;
int getLength(node* l) ;
void insert(node** l,string word,int position) ;
node* ifItExistsRetPrec(node* l,string word) ;
string delete(node** l,string word) ;
void freeList(node** l) ;
bool ifItExists(node* l,string word) ;

#endif 