#ifndef STATICHEAP_H
#define STATICHEAP_H

#include <stdbool.h>

#define MAX_HEAP_SIZE 100

// Min Heap structure with static memory allocation
// This implementation works for distinct (non-equal) values only
// Maximum capacity: 100 elements
typedef struct heap
{
   int t[MAX_HEAP_SIZE];
   int length;
}heap;

// Utility Functions
void perm(int* v1, int* v2);
int getParentIndex(int i);
int getMin(int a, int b, int c);

// Heap Operations
void insert(heap* h, int val);
heap createHeap(int t[], int n);
int delValHeap(heap* h, int val);

// Search Operations
bool SearchValHeap(heap h, int val);
int SearchValIndexHeap(heap h, int val);

// Display
void printHeap(heap h);

// Sorting (for arrays with length <= 100)
void HeapSort(int array[], int length);

#endif // STATICHEAP_H