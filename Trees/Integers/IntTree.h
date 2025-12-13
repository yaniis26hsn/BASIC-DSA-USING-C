#ifndef INTTREE_H
#define INTTREE_H

#include <stdbool.h>

typedef struct node {
    int val;
    struct node *right;
    struct node *left;
} node;

// general tree functions
node* createTree(int data);
void freeTree(node* root);
int countNodes(node* tree);
bool isLeaf(node* tree);
bool TreeCmp(node* tree1, node* tree2);
bool TreeFormCmp(node* tree1, node* tree2);
bool findVal(node* tree, int data);
node* findValParent(node* tree, int data);
void insert(node** tree, int data);

// BST functions but some of them may work for any binary trees like deletvalbst
bool findValBst(node* tree, int data);
node* findValPosBst(node* tree, int data);
node* findValParentBst(node* tree, int data);
void insertBST(node** tree, int data);
int deleteValBst(node** tree, int data);
int GetAndDeleteSuccessor(node** tree);
void printBstAscending(node* tree);
node* createBst(int array[], int length);

// utility
void swap(int* a, int* b);
void sortArray(int array[], int start, int end);
int partition(int array[], int start, int end);

#endif