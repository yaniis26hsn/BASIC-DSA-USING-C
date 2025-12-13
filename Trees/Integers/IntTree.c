#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// the most of this fnc are effective for trees that doesn t have a duplicate values , however you can call them even in that case 
// you can outsmart it by coding tricks example : call delete untill the it returns a wrong number , this will delete all the values even
// even that we didn t made it to do that
typedef struct node
{
int val ;
struct node *right ;
struct node *left ;
}node;
void swap(int* a, int* b){
    int tmp = *a ;
    *a = *b ;
    *b = tmp ;
}

bool isLeaf(node* tree) {
    
    if(tree == NULL) return false ;
    return (tree->left==NULL && tree->right==NULL ) ;
} 
bool TreeCmp(node* tree1 ,node* tree2){
    if(tree1 == NULL && tree2 == NULL) return true ;
    if(tree1 == NULL && tree2 != NULL) return false ;
    if(tree2 == NULL && tree1 != NULL) return false ;
    
    return (TreeCmp(tree1->right,tree2->right) && TreeCmp(tree1->left,tree2->left) && tree1->val==tree2->val);
}
bool findVal(node* tree ,int data){
    if(tree==NULL) return false ;
    if (tree->val==data) // we could replace this condition by return tree->val==data but it would be ambiguous
    {
        return true ; 
    }
    
    return (findVal(tree->left,data) || findVal(tree->right,data)) ;
}

node* findValParent(node* tree ,int data){
    // this fnc returns a pointer to the parent of the node that has the value data 
    // make sure that the value exists or you get null and the value it not on the root (the root has no parent)
    if(tree==NULL) return NULL ;
    if(isLeaf(tree)) return NULL ;
    if(tree->left != NULL){
        if (tree->left->val==data ) {
        return tree ;
    }
    }
    if(tree->right != NULL){
    if(tree->right->val==data){
        return tree ;
    }
}
     node* leftSideRes = findValParent(tree->left,data) ;
    if(tree->left != NULL &&  leftSideRes != NULL) return leftSideRes ;
    if(tree->right != NULL) return findValParent(tree->right,data) ;
    
    return NULL ;
}

node* findValPosBst(node* tree,int data){
    if(tree==NULL) return NULL ;
    if(tree->val == data) return tree ;
     if(data < tree->val) return findValPosBst(tree->left,data) ;
     if(data > tree->val) return findValPosBst(tree->right,data) ;
     // make sure that the left value is the smaller and the bigger on the right not the inverse 
     return NULL ; // just for the compiler 
}
/*
bool ifaBST(node* tree){
   
 if(tree == NULL) return true ;
 if(tree->right != NULL && tree->left == NULL) return (tree->right->val > tree->val)  && ifaBST(tree->right)  ;
 if(tree->left != NULL && tree->right == NULL) return (tree->left->val < tree->val)  && ifaBST(tree->left)  ;
 if(tree->left != NULL && tree->right != NULL) return (tree->left->val < tree->val)  && ifaBST(tree->left) && ifaBST(tree->right) && (tree->right->val > tree->val) ;
 if(tree->left == NULL && tree->right == NULL) return true ;
 return true ; // just for the compiler
}
*/
node* createTree(int data){
    node* n = (node*) malloc(sizeof(node)) ;
    n->val = data ;
    n->left = NULL ;
    n->right = NULL ;
    return n; 

}
int countNodes(node* tree){
    if(tree==NULL) return 0 ;
    return countNodes(tree->left) + countNodes(tree->right) + 1;
}
void insert(node** tree,int data){
    // this insertion fnc gonna keep the tree balanced it is not made for BST 
    if(*tree==NULL) {
   *tree = createTree(data) ;
        return ;
    }
    if(countNodes((*tree)->left)>countNodes((*tree)->right)) insert(&(*tree)->right,data) ;
    else insert(&(*tree)->left,data) ;
}
node* findValParentBst(node* tree,int data){
    // you will get a NULL if you the value is on the root . you should know that 
    if(tree == NULL) return NULL ;
    if(isLeaf(tree)) return NULL ;
    if(tree->left != NULL){
        if(tree->left->val == data) return tree ;
    }
    
    if(tree->right != NULL){
        if(tree->right->val == data) return tree ;
    }
    if(data < tree->val && tree->left != NULL) return  findValParentBst(tree->left,data) ;
    if(data > tree->val && tree->right != NULL) return findValParentBst(tree->right,data) ;

    return NULL ; // just in case of any error 
}


void printBstAscending(node* tree){
// we will use Left parent right (LPD) (infixe)  it gives us what we want directly 
if(tree == NULL) return ;
printBstAscending(tree->left) ; // 1
printf(" %d ",tree->val) ;
printBstAscending(tree->right) ; // 2
// use the DPL (swap 1 and 2 to get DPL) to get descending order 
}
// void printTreeInForm() {for later ...}

int partition(int[] array ,int start,int end){
    // this fnc is working with sortArray fnc 
    int pivot = array[end] ;
    int i = start - 1 ;
    for(int j = start ;j<end ; j++){
        if(array[j]<pivot){
         i++ ;
         swap(&array[i],&array[j]) ;
        }
    }
    i++ ;
    swap(&array[i],&array[end]) ;
    return i ;
}

void sortArray(int array[],int start,int end){
    // we will need this fnc in createBst fnc
    // we will use quick sort
    // end is length - 1
    if(end<=start) return ;
    int pivot = partition(array,start,end) ;
    sortArray(array,start,pivot-1)  ;
    sortArray(array,pivot+1,end) ;

}
/*
node* createAVL(int array[] ,int length){
    // the array gonna change (get sorted with asending order)after calling this func . send a copy if you want to keep the original
    sortArray(array,0,length - 1) ;
    // to be continued

}*/

node* createBst(int array[] ,int length){
   
    if(length==0) return NULL ;
    node* tree = createTree(array[0]) ;
    for(int i = 1 ; i<length ; i ++ ){
        insert(&tree,array[i]) ;
    }
    return tree ;
}

void freeTree(node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

bool TreeFormCmp(node* tree1 ,node* tree2){
    // compare if two tree has the same form . not necessarly the same values just the shape(structure,form,look)
    if (tree1 == NULL && tree2 == NULL) return true ;
    if(tree1 == NULL && tree2 != NULL) return false ;
    if(tree2 == NULL && tree1 != NULL) return false ;
    
    return (TreeFormCmp(tree1->right,tree2->right) && TreeFormCmp(tree1->left,tree2->left) );
}
bool findValBst(node* tree,int data){
    if(tree==NULL) return false ;
    if(tree->val == data) return true ;
     if(data < tree->val) return findValBst(tree->left,data) ;
     if(data > tree->val) return findValBst(tree->right,data) ;
     // make sure that the left value is the smaller and the bigger on the right not the inverse 
     return false ; // this line is unnecessary logically but to make sure that the complier we won't warn us
     // about a case where won't return something . but logically there will a return and we will never execute this last line

}
void insertBST(node** tree,int data){
    if(*tree == NULL) {
        *tree = createTree(data);
        return ;
    }
    if((*tree)->val == data) {
        printf("value already exists") ; return ;
    } 
    else if((*tree)->val < data) insertBST(&((*tree)->right),data) ;
    else insertBST(&((*tree)->left),data) ; // this means (*tree)->val > data

}
int deleteValBst(node** tree,int data) ;
int GetAndDeleteSuccessor(node** tree){
    // you can t call this fnc for a leaf and if it hasn t a right child 
 // we will check anyway 
    if(!isLeaf(*tree) && (*tree)->right != NULL){
      node* succesor = (*tree)->right ;
      
      while(succesor->left != NULL) {
        succesor = succesor->left ;
      }
      int RetVal = succesor->val ;
      return deleteValBst(&((*tree)->right),RetVal) ; // 
      // this last call gonna delete the succesor 
      // it gonna work since the succoesor is never a double childed there no left child
      // this case of deletion doesnt need this func only double childed needs this fnc 
      // so there will be no infinite calls case (a fnc1 calls fnc2 and fnc 2 calls fnc1)
       

    }
    printf("error :node is not a leaf or node has no right child, there is no succesor ") ;
    return -1 ; // just a value to prevent errors . if you got -1 this either there was an error or no error the succesor had -1 
    // make sure that !isLeaf(*tree) && (*tree)->right != NULL to be sure that there was no mistake

    // later we make this func delete locally the succor for more effeicincy 
}
int deleteValBst(node** tree,int data){
    // this fnc will delete a node inside a BST 
    // it works with a normal binary tree too , you can use it with it
    // we will return the deleted value 
    // if the value doesnt exist we will return a value different than the parameter as a sign
    if(!findValBst(*tree,data)) {printf("error : the value doesnt exist ") ;
      return data +  1 ;
        
    }
    else { 
        // the value exists
        int delVal ;
        node* position = findValPosBst(*tree,data);
         // position is a pointer to the node that we want to delete , i couldn t think of a better name 
        if( position != *tree && ((position->left == NULL && position->right != NULL) || (position->right == NULL && position->left != NULL))){
       // no need check that it is not a leaf we are sure that it has exactly one child 
            // a middle placed node with only one child not a root
           
           node* dadPosition = findValParentBst(*tree,data) ;

        if(dadPosition->right == position) {
            if(position->right != NULL) dadPosition->right = position->right ;
           else if(position->left != NULL) dadPosition->right = position->left ; // there was no need for that condition we just added it for clarity
        }
        if(dadPosition->left == position) {
            if(position->right != NULL) dadPosition->left = position->right ;
          else if(position->left != NULL) dadPosition->left = position->left ; // there was no need for that condition we just added it for clarity

        }
         free(position) ;
         return data ;
        }
        else if(*tree == position && ((*tree)->left == NULL || (*tree)->right == NULL) ){
            // the val is in the root either as a leaf or  one childed but not two childed
            if(position->left == NULL && position->right == NULL)  *tree = NULL ;
        
            else if(((position->left == NULL && position->right != NULL) || (position->right == NULL && position->left != NULL))){
         if(position->left != NULL)  *tree = position->left ; 
         if(position->right != NULL)  *tree = position->right ;
        }
          
               free(position) ;
                return data ;
        } 
       
        else if(position != *tree && position->left != NULL && position->right != NULL ){
            // a node with two childs ( middle node)
            node* dadPosition = findValParentBst(*tree,data) ;
            node** PosPtr = (dadPosition->left == position) ? &(dadPosition->left) : &(dadPosition->right) ; 
           int successorVal = GetAndDeleteSuccessor(PosPtr) ;
           delVal = position->val ;
           position->val = successorVal ;
           return delVal ;

        }
        else if(position == *tree && position->left != NULL && position->right != NULL ){
            // the root with two childs
            int successorVal = GetAndDeleteSuccessor(tree) ;
            delVal = (*tree)->val ;
            (*tree)->val = successorVal ;
            return delVal ;

        }
        else if(position->left == NULL && position->right == NULL){
            // leaf position But not the root is leaf , the case was dealt with in that case before
        node* dadPosition = findValParentBst(*tree,data) ;
        
            delVal = position->val ;
            if(dadPosition->right == position) dadPosition->right = NULL ;
             if(dadPosition->left == position) dadPosition->left = NULL ;
            free(position) ;

            return delVal ;
    
        }
    }
    return 0 ; // only for the compiler 
}/*
int getAndFreeRightmostLeaf(node* tree){
// this gonna be used in delete normal val in binary tree fnc 
// project reported
}
*/
/* we will replace the deleted node by the right most leaf
void delete(node** tree,int data){
// this fnc gonna be replaced with deleteValBst since it works the the normal binary tree two
 // so you call deleteValBst for it
    node* tmp ;
    if((*tree)->val == data) {
        tmp = *tree ;
        if((*tree)->right != NULL){ 
            *tree = (*tree)->right ;
            
        }
         
        freeTree(tmp) ;
        return ;
    }
    node* parent = findValParent(*tree,data) ;
    // if the val is in the root 
    
}*/

// for insert() we will try to upgrade it later by  avoiding counting nodes each time for effecincy
// you can use deleteValBst for a normal binary tree

