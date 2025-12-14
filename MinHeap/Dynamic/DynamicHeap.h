#ifndef DYNAMICHEAP_H
#define DYNAMICHEAP_H

#include <stdbool.h>

// Min Heap structure with dynamic memory allocation
// This implementation works for distinct (non-equal) values only
typedef struct heap
{
   int* t;
   int length;
   int capacity;
}heap;

// Utility Functions
void perm(int* v1, int* v2);
int getParentIndex(int i);
int getMin(int a, int b, int c);

// Heap Operations
void insert(heap* h, int val);
heap createHeap(int t[], int n);
int delValHeap(heap* h, int val);
void freeHeap(heap* h);

// Search Operations
bool SearchValHeap(heap h, int val);
int SearchValIndexHeap(heap h, int val);

// Display
void printHeap(heap h);

// Sorting
void HeapSort(int array[], int length);

#endif // DYNAMICHEAP_H