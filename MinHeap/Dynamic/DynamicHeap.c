#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "DynamicHeap.h"
// this is MinHeap . to get max heap you can do simple changes like inverse some comparision 
// this heap implementation , in genearal , accept only one occurance of a single value . no more 
// however maybe you can use it for multiple occurances case
      // since we start from 0 the left child will be at 2*index+1 and the right child at 2*index + 2
      // about the parent it s a formula , i made fnc for that
typedef struct heap
{
   int*t ;
   int length ;
   int capacity ;
}heap;

void perm(int* v1,int* v2){
   int tmp = *v1 ;
   *v1 = *v2 ;
   *v2 = tmp ;
}
int getParentIndex(int i) {
   int parentIndex = (i+1)/2 - 1 ;
   return parentIndex ;
}
int getMin(int a ,int b, int c){
   if(a<b) {
      if(a<c) return a ;
      else return c ; // c<a<b
   }
   else{ // b<a
      if(b<c) return b; 
      else return  c ;    // c<b<a
   }
      // this is used for non equal valued parameters . 
      // this was one of my old programs that i did . i could simplify i wanned to keep that old solution
}

void insert(heap* h,int val){
   if(h->length >= h->capacity){
      // length will never be over capacity but for safety we checked for safety
      h->capacity += 20 ; // we will 20 each time 
      h->t = realloc(h->t,h->capacity * sizeof(int)) ;
      if(!h->t) exit(1) ;
   }
   (*h).t[(*h).length] = val ;
   (*h).length ++ ;
   int counter = (*h).length - 1;
  
   while ((*h).t[counter] < (*h).t[getParentIndex(counter)] && counter>=1)
   {
    perm(&(*h).t[counter],&(*h).t[getParentIndex(counter)]) ;
    counter = getParentIndex(counter) ;
   }
   
}


heap createHeap(int t[],int n){
  heap h ; 
  h.capacity = n + 10 ;// the extra 10 was just for possible insertion later
   h.t = (int*) malloc(sizeof(int) * h.capacity ) ;  
   if(!h.t) exit(1) ;
 h.length = 0;
    for(int i=0;i<n;i++){
      insert(&h,t[i]) ;
    }
    return h ;
}
void printHeap(heap h){
   for(int i=0;i<h.length;i++){
      printf(" %d ",h.t[i]) ;
   }
}
bool SearchValHeap(heap h,int val){
  
   for(int i=0;i<h.length;i++){
     if(h.t[i] == val) return true ;
   }
   return false ;
}

int SearchValIndexHeap(heap h,int val){
   for(int i=0;i<h.length;i++){
     if(h.t[i] == val) return i ;
   }
   return -1 ; // the val doesn t exist in the heap
}
int delValHeap(heap* h, int val){
   int index = SearchValIndexHeap(*h, val);
   if(index != -1){
    
   
   (*h).t[index] = (*h).t[(*h).length - 1];
   (*h).length--; 
   
   while (index < h->length) 
   { 
     if(2*index + 2 < h->length){
// two childed case
       int min = getMin(h->t[index],h->t[2*index + 1],h->t[2*index + 2]) ;
      if( min == h->t[2*index + 1] ){
         perm(&(*h).t[2*index + 1], &(*h).t[index]);
         index = index * 2 + 1;
      }
      
      else if(min == h->t[2*index + 2] ){
         perm(&(*h).t[2*index + 2], &(*h).t[index]);
         index = index * 2 + 2;
      }
      
      else if(min == h->t[index] ){ 
         // no need for the condition we made just for clarity
        break;
      }
   }
   else if(2*index + 1 < h->length){
      // one childed : this means that the child is a leaf . we will check if we will do a last permutation . 
      if(h->t[2*index + 1] < h->t[index]){
         perm(&h->t[2*index + 1] , &h->t[index]) ;
         index = 2*index + 1 ;
         break;
      }
      else 
      break;
   
   }
   else{
      // a leaf case , there is nothing to do (i am not sure that there is a possibitity to enter here anyway ) . however i made it for safety
      break;
   }
   }
   return val ;
   }
   return val + 5; 
   // in case of an error we will return a value different than the parameter sent , it a smart sign
   
}
void freeHeap(heap* h) ;
void HeapSort(int array[],int length){
   // ascending order
  
   heap h = createHeap(array,length) ;
   for(int i = 0 ;i<length;i++){
      array[i] = delValHeap(&h,h.t[0]) ;  // in a Minheap the the root is the min
   }
   freeHeap(&h) ;
}

void freeHeap(heap* h){
   free(h->t) ;
   h->t = NULL ;
   h->capacity = 0 ;
   h->length = 0 ;
}