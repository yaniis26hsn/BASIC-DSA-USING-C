#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef char* string ;
typedef struct node
{
 string val;
struct node *right ;
struct node *left ;
}node;
// freeTree(node* tree){ // we will not to free the string inside the node too .} for later 

node* createTree(string data); // forward declaration

bool findValBst(node* tree,string data){
    if(tree==NULL) return false ;
    if(strcmp(tree->val,data)==0) return true ;
     if(strcmp(tree->val,data) < 0) return findValBst(tree->right,data) ;
     if(strcmp(tree->val,data) > 0) return findValBst(tree->left,data) ;
     // make sure that the left value is the smaller and the bigger on the right not the inverse 
     return false ; // this line is unnecessary logically but to make sure that the complier we won't warn us
     // about a case where won't return something . but logically there will a return and we will never execute this last line
}

void insertBST(node** tree,string data){
    if(*tree == NULL) {
        *tree = createTree(data);
        return ;
    }
    if(strcmp((*tree)->val,data)==0) {
        printf("value already exists") ; return ;
    } 
    else if(strcmp((*tree)->val,data)<0) insertBST(&((*tree)->right),data) ;
    else insertBST(&((*tree)->left),data) ; // this means (*tree)->val > data as strings of course 

}

node* createTree(string data){
    node* n = (node*) malloc(sizeof(node)) ;
    n->val = (char*) malloc(strlen(data) + 1);
    strcpy(n->val,data) ;
    n->left = NULL ;
    n->right = NULL ;
    return n; 

}

node* findValPosBst(node* tree,string data){
    if(tree==NULL) return NULL ;
    if(strcmp(tree->val,data) == 0) return tree ;
     if(strcmp(tree->val,data) > 0) return findValPosBst(tree->left,data) ;
     if(strcmp(tree->val,data) < 0) return findValPosBst(tree->right,data) ;
     // make sure that the left value is the smaller and the bigger on the right not the inverse 
}

bool isLeaf(node* tree) {
    
    if(tree == NULL) return false ;
    return (tree->left==NULL && tree->right==NULL ) ;
} 

node* findValParentBst(node* tree ,string data){
    // this fnc returns a pointer to the parent of the node that has the value data 
    // make sure that the value exists or you get null and the value it not on the root (the root has no parent)
    if(tree==NULL) return NULL ;
    if(isLeaf(tree)) return NULL ;
    if(tree->left != NULL){
        if (strcmp(tree->left->val,data)==0) {
        return tree ;
    }
    }
    if(tree->right != NULL){
    if(strcmp(tree->right->val,data)==0){
        return tree ;
    }
}
     node* leftSideRes = findValParentBst(tree->left,data) ;
    if(tree->left != NULL &&  leftSideRes != NULL) return leftSideRes ;
    if(tree->right != NULL) return findValParentBst(tree->right,data) ;
    
    return NULL ;
}
string deleteValBst(node** tree, string data) ;

string GetAndDeleteSuccessor(node** tree){
    // you can t call this fnc for a leaf and if it hasn t a right child 
 // we will check anyway 
    if(!isLeaf(*tree) && (*tree)->right != NULL){
      node* succesor = (*tree)->right ;
      
      while(succesor->left != NULL) {
        succesor = succesor->left ;
      }

      string RetVal = (char*) malloc(strlen(succesor->val) + 1) ;
      strcpy(RetVal,succesor->val ) ;
      return deleteValBst(&((*tree)->right),RetVal) ; // you need to free RetVal . 
      // this last call gonna delete the succesor 
      // it gonna work since the succoesor is never a double childed there no left child
      // this case of deletion doesnt need this func only double childed needs this fnc 
      // so there will be no infinite calls case (a fnc1 calls fnc2 and fnc 2 calls fnc1)
       

    }
    printf("error :node is not a leaf or node has no right child, there is no succesor ") ;
    return NULL ; // just a value to prevent errors . if you got -1 this either there was an error or no error the succesor had -1 
    // make sure that !isLeaf(*tree) && (*tree)->right != NULL to be sure that there was no mistake

    // later we make this func delete locally the succor for more effeicincy 
    
}
char* deleteValBst(node** tree, const char* data) {
    if (!findValBst(*tree, data)) {
        // value doesn't exist, return special string
        char* err = (char*) malloc(strlen(data) + 12); // "wronginput" + '\0'
        sprintf(err, "wronginput%s", data);
        return err;
    }

    node* position = findValPosBst(*tree, data);
    char* delVal = (char*) malloc(strlen(position->val) + 1);
    strcpy(delVal, position->val);

    // Case 1: middle node with one child
    if (position != *tree && ((position->left == NULL) != (position->right == NULL))) {
        node* dadPosition = findValParentBst(*tree, data);
        node* child = (position->left != NULL) ? position->left : position->right;

        if (dadPosition->left == position) dadPosition->left = child;
        else dadPosition->right = child;

        free(position->val);
        free(position);
        return delVal;
    }

    // Case 2: root with zero or one child
    if (*tree == position && (position->left == NULL || position->right == NULL)) {
        node* child = (position->left != NULL) ? position->left : position->right;
        *tree = child;
        free(position->val);
        free(position);
        return delVal;
    }

    // Case 3: middle node with two children
    if (position != *tree && position->left != NULL && position->right != NULL) {
        node* dadPosition = findValParentBst(*tree, data);
        node** PosPtr = (dadPosition->left == position) ? &(dadPosition->left) : &(dadPosition->right);
        char* successorVal = GetAndDeleteSuccessor(PosPtr);
        free(position->val);
        position->val = successorVal;
        return delVal;
    }

    // Case 4: root with two children
    if (position == *tree && position->left != NULL && position->right != NULL) {
        char* successorVal = GetAndDeleteSuccessor(tree);
        free((*tree)->val);
        (*tree)->val = successorVal;
        return delVal;
    }

    // Case 5: leaf node (non-root)
    node* dadPosition = findValParentBst(*tree, data);
    if (dadPosition) {
        if (dadPosition->left == position) dadPosition->left = NULL;
        if (dadPosition->right == position) dadPosition->right = NULL;
    }
    free(position->val);
    free(position);
    return delVal;
}