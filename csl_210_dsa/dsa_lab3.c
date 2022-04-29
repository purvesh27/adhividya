#include "csl210_lab3.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_HT 100
#define SPACE_GAP_LEVEL 5

struct MinHeap{
    unsigned size;
    unsigned capacity;
    struct btNode** array;
};

btNode_t* newNode(char data, unsigned frequency){
    btNode_t* temp = (btNode_t*)malloc(sizeof(btNode_t));
    temp->left = NULL;
    temp->right = NULL;
    temp->value = data;
    temp->frequency = frequency;
    return temp;
}

char *removeDuplicate(char str[], int n, int* retSize)
{
   int index = 0;
   for (int i=0; i<n; i++) {
     int j; 
     for (j=0; j<i; j++)
        if (str[i] == str[j])
           break;

     if (j == i)
        str[index++] = str[i];
   }
    //printf("index : %d \n", index);
    *retSize = index-1;
   return str;
}

int* findFrequncy(char S[], int freq[])
{
    int i = 0;
    while (S[i] != '\0') {
        freq[S[i] - 'a']++;
        i++;
    }
    return freq;
}


struct MinHeap* createMinHeap(unsigned capacity){
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (btNode_t**)malloc(minHeap->capacity*sizeof(btNode_t*));
    return minHeap;
}

void swapbtNode_t(btNode_t** a, btNode_t** b){
    btNode_t* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx){
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;
    if (left < minHeap->size
        && minHeap->array[left]->frequency
               < minHeap->array[smallest]->frequency)
        smallest = left;
 
    if (right < minHeap->size
        && minHeap->array[right]->frequency
               < minHeap->array[smallest]->frequency)
        smallest = right;
 
    if (smallest != idx) {
        swapbtNode_t(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }

}

int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}
 
btNode_t* extractMin(struct MinHeap* minHeap)
{
   btNode_t* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, btNode_t* minHeapNode){
 
    ++minHeap->size;
    int i = minHeap->size - 1;
 
    while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency) {
 
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
 
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
 
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int isLeaf(btNode_t* root){
    return !(root->left) && !(root->right);
}
 
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size){
 
    struct MinHeap* minHeap = createMinHeap(size);
 
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
 
    minHeap->size = size;
    buildMinHeap(minHeap);
 
    return minHeap;
}

btNode_t* buildHuffmanTree(char data[], int freq[], int size){
    btNode_t *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->frequency + right->frequency);
 
        top->left = left;
        top->right = right;
 
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}


btNode_t* createHuffmanTree(char input[], unsigned short sz){
    int freq[26] = {0};
    int modSize = 0;
    int* freqArr = findFrequncy(input, freq);
    char* a = removeDuplicate(input, sz, &modSize);
    //printArray(a, modSize);
    //printArray(input, sz);
    //printFrequencyArray(freqArr, modSize);
    btNode_t* head = buildHuffmanTree(a, freqArr, modSize);
    return head;
}


