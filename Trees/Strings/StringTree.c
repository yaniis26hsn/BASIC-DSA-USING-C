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


bool findValBst(node* tree,string data){
    if(tree==NULL) return false ;
    if(strcmp(tree->val,data)==0) return true ;
     if(strcmp(tree->val,data) < 0) return findValBst(tree->left,data) ;
     if(strcmp(tree->val,data) > 0) return findValBst(tree->right,data) ;
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
     return NULL ; // just for the compiler 
}

bool isLeaf(node* tree) {
    
    if(tree == NULL) return false ;
    return (tree->left==NULL && tree->right==NULL ) ;
} 

node* findValParent(node* tree ,string data){
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
     node* leftSideRes = findValParent(tree->left,data) ;
    if(tree->left != NULL &&  leftSideRes != NULL) return leftSideRes ;
    if(tree->right != NULL) return findValParent(tree->right,data) ;
    
    return NULL ;
}
string deleteValBst(node** tree,string data) ;
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

string deleteValBst(node** tree,string data){
    // this fnc will delete a node inside a BST 
    // it works with a normal binary tree too , you can use it with it
    // we will return the deleted value 
    // if the value doesnt exist we will return a value different than the parameter as a sign
    if(!findValBst(*tree,data)) {
    printf("error : the value doesn't exist\n");
    char* err = (char*) malloc(strlen(data) + 11 + 1); // 11 for "wronginput" + 1 for '\0'
    if(!err) return NULL; // allocation failed
    sprintf(err, "wronginput%s", data);
    return err;
}

    else { 
        // the value exists
        
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
         free(position->val) ;
         free(position) ;
         return data ;
        }
        else if(*tree == position && ((*tree)->left == NULL || (*tree)->right == NULL) ){
            // the val is in the root either as a leaf or  one childed but not two childed
            if(position->left == NULL && position->right == NULL)  *tree = NULL ; // leaf 
        
            else if(((position->left == NULL && position->right != NULL) || (position->right == NULL && position->left != NULL))){
         if(position->left != NULL)  *tree = position->left ; 
         if(position->right != NULL)  *tree = position->right ;
        }
               free(position->val) ;
               free(position) ;
                return data ;
        } 
       
        else if(position != *tree && position->left != NULL && position->right != NULL ){
            // a node with two childs ( middle node)
            node* dadPosition = findValParentBst(*tree,data) ;
            node** PosPtr = (dadPosition->left == position) ? &(dadPosition->left) : &(dadPosition->right) ; 
            // we needed to send the parent node left or right to avoid sending a copy of the subtree . like this we will delete from the real tree
            string successorVal = GetAndDeleteSuccessor(PosPtr);
            free(position->val) ;
            position->val = successorVal ;
           return data ;

        }
        else if(position == *tree && position->left != NULL && position->right != NULL ){
            // the root with two childs
            string successorVal  = GetAndDeleteSuccessor(tree) ;
            free((*tree)->val) ;
            (*tree)->val = successorVal ;
            return data ;

        }
        else if(position->left == NULL && position->right == NULL) { // this condition was just for clarity . that is the only remaining case 
            // leaf position But not the root is leaf , the case was dealt with in that case before
        node* dadPosition = findValParentBst(*tree,data) ;
            if(dadPosition->right != NULL) {
                if(strcmp(dadPosition->right->val,data)== 0) dadPosition->right = NULL ; // here we could compare dadPosition->right == position instead of their values like in int version but both work 
            }
            if(dadPosition->left != NULL) { // we could write an else but we would to keep the code clearer
            if(strcmp(dadPosition->left->val,data)== 0) dadPosition->left = NULL ;  // same as right case 
            }
            free(position->val) ;
            free(position) ;

            return data ;
    
        }
    }
    return NULL ; // just for the compiler
}


void freeTree(node* root) {
    if (!root) return; 
    free(root->val) ;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
