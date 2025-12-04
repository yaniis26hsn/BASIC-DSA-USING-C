#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef char* string ;
typedef struct node
{
    string val ;
    struct node* next ;
}node;
node* createNode(string data) {
    node* l =  malloc(sizeof(node)) ;
    l->val = malloc(strlen(data) + 1); // +1 for the null terminator
    strcpy(l->val, data);
    l->next = NULL ;
    return l;
}
int getLength(node* l){
    int length = 0 ;
    node* tmp = l ;
    while(tmp!=NULL){
        length ++ ;
        tmp = tmp->next ;
    }
     return length ;
}
void insert(node** l,string word,int position){
    // the position starts from 0 to (length-1) like any static list, you should know that 
    if(position<0 || position>getLength(*l)){ printf("position it's not valid") ; return ;}
    node* n = createNode(word) ;
    if(position==0){
     n->next= *l ;
    *l = n ;
    }else{ // maybe it works for position 0 too but i decided to deal with it by a the special code above
       // update , i had to deal with position by it own 
        node* precedent = *l ;
        while (position>1)
        {
            precedent = precedent->next ;
            position-- ;
        }
        n->next = precedent->next ;
        precedent->next = n ;
    }
    
}

node* ifItExistsRetPrec(node* l,string word){
    // this fnc will return the address of the precendent node(with other words a pointer to that one)  that contains the word 
    //otherwise null if it doesnt exist 
    //otherise null if it is the first node because there is no precedent you can use it as an
    // do your tests to differ between first node case and no existence case to differ between the two case as in delete fnc
    // if the l->val!= word means the is no "word" in that list , better than checking if it is missing by using ifItexists fnc it will check all the nodes 
    // this fnc is very usefull with dynamic lists 

    
    
    // strcmp returns 0 when they are the same you should know that 
    node* precedent = l;
    node* tmp = l->next ;
    
     while(tmp != NULL){
        if(strcmp(tmp->val,word)==0) return precedent ;
        tmp = tmp->next ;
        precedent = precedent->next ;
    }
    
    return NULL ;

}
// i made the delete fnc return the data deleted for no reason , maybe to look like the pop fnc for stacks
string delete(node** l,string word){
    if(*l == NULL) return "NotFoundError" ;
    node* precPos = ifItExistsRetPrec(*l,word) ;
    node* tmp ;
    if(precPos == NULL && strcmp((*l)->val, word) != 0) {
        return "NotFoundError" ;
    } 
    else if(precPos == NULL && strcmp((*l)->val, word) == 0){
         // this means it is the word is in first node , go to  ifItexistsRetPrec fnc to understand
          tmp = *l ;
         *l = (*l)->next ;
         free(tmp) ;
      return word ;
    }
    tmp = precPos->next ;
    precPos->next = (precPos->next)->next ;
    string retVal = tmp->val ;
    free(tmp) ;
    /**
 * delete(): deletes the node containing 'word' and returns its string.
 * The caller is responsible for calling free() on the returned string.
 */

    return retVal ;
    
} 


void freeList(node** l){
    node* tmp ;
    while (*l!=NULL)
    {
        tmp = *l ;
        *l = (*l)->next ;
        free(tmp->val) ;
        free(tmp) ;
    }
}
bool isEmpty(node* l){
    return (l==NULL) ;
}
bool ifItExists(node* l,string word){
    node* tmp ;
    tmp = l ;
    // strcmp returns 0 when they are the same
    while(tmp != NULL){
        if(strcmp(tmp->val,word)==0) return true ;
        tmp = tmp->next ;
    }
    return false ;
}


