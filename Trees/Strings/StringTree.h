#ifndef STRINGTREE_H
#define STRINGTREE_H

#include <stdbool.h>

typedef char* string;

typedef struct node {
    string val;
    struct node *right;
    struct node *left;
} node;

// general tree functions
node* createTree(string data);
void freeTree(node* root);
bool isLeaf(node* tree);
node* findValParent(node* tree, string data);

// BST functions , but in some cases they can work with normal binary trees like deletevalbst
bool findValBst(node* tree, string data);
node* findValPosBst(node* tree, string data);
node* findValParentBst(node* tree, string data);
void insertBST(node** tree, string data);
string deleteValBst(node** tree, string data);
string GetAndDeleteSuccessor(node** tree);

#endif