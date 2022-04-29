#include "csl102_lab8.h"
#include <stdlib.h>

short treeArray[1000];
int idx = 0;
int count = 0;
int j = 0;
short arr[1000];
int midx = 0;
void i(nodeQ_t* node , short Arr[], short* idx){
    if(EMPTYNODE==node) 
    return;

    i(node->left , Arr , idx);

    Arr[*idx]=node->data;
    (*idx)++;

    i(node->right , Arr, idx);
} 

short cn(nodeQ_t* node){
    
    
    if(EMPTYNODE == node) 
    return 0;


    return (cn(node->left)+ cn(node->right) + 1);
}


short* mrg(short arr1[], short arr2[], int x , int y){
    
    
    short* arr = (short*)malloc(sizeof(short*)*(x+y));
    
    
    short a=0;
    short b = 0;
    short k = 0;

    while (a<x && b<y){
        if(arr1[a] < arr2[b]){
        arr[k] = arr1[a];
        a++;
        }
        else{
            arr[k] = arr2[b];
            b++;
        }
        k++;
    }

    while (a < x){
        arr[k] = arr1[a];
        a++;
        k++;

    }

    while(b < y){
        arr[k] = arr2[b];
        b++;
        k++;
    }


    return arr;
}

nodeQ_t* sab(short arr[], short s, short e){
    
    if(s>e) 
    return EMPTYNODE;

    short c = (s + e)/2;


    nodeQ_t* node = createNode(arr[c]);

    node->left = sab(arr,s,c-1);


    node->right = sab(arr,c+1,e);



    return node;
}



nodeQ_t* getParentNodeBST(nodeQ_t* node, short val){

    while(EMPTYNODE != node){
        if ((val > node->data) && (node->right != EMPTYNODE))     
            node = node->right;
        else if ((val > node->data) && (node->right == EMPTYNODE))
            return node;
        else if ((val < node->data) && (node->left != EMPTYNODE))    
            node = node->left;
        else if ((val < node->data) && (node->left == EMPTYNODE))
            return node;
        else
            return EMPTYNODE;
    }

    return EMPTYNODE;
}


void insertNodeInBST(nodeQ_t* root, nodeQ_t* newNode){

    if(EMPTYNODE == root || EMPTYNODE == newNode)
        return;

    nodeQ_t* parent = getParentNodeBST(root, newNode->data);
    if(EMPTYNODE == parent)
        return;

    if(newNode->data > parent->data)
        parent->right = newNode;
    if(newNode->data < parent->data)
        parent->left = newNode;
}


void swap(short *a, short *b)
{
    short temp = *a;
    *a = *b;
    *b = temp;
}
  
void selectionSort(short arr[], int n){
    int minIdx = 0;
    for (int i = 0; i < n-1; i++){
        minIdx = i;
        for (int j = i+1; j < n; j++){
          if (arr[j] < arr[minIdx]){
            minIdx = j;
            }
        }
        swap(&arr[minIdx], &arr[i]);
    }
}

void bintreetoarr(nodeQ_t* node){
    if(node == EMPTYNODE){
        return;
    }
    bintreetoarr(node->left);
    treeArray[idx] = node->data;
    idx++;
    bintreetoarr(node->right);
}

void a(nodeQ_t* node){
    if(node == EMPTYNODE){
        return;
    }
    a(node->left);
    arr[midx] = node->data;
    midx++;
    a(node->right);
}

int calSize(nodeQ_t* node){
    if(node == EMPTYNODE){
        return 0;
    }
    calSize(node->left);
    count++;
    calSize(node->right);
    return count;
}
  
nodeQ_t* createBST(nodeQ_t* node){
    if(node == EMPTYNODE){
        return EMPTYNODE;
    }
    createBST(node->left);
    node->data = treeArray[j];
    j++;
    createBST(node->right);
    return node;

}

 
nodeQ_t* createNode(short value){
    nodeQ_t* node = (nodeQ_t*)malloc(sizeof(nodeQ_t));
    node->data = value;
    node->left = EMPTYNODE;
    node->right = EMPTYNODE;
    return node;
}
nodeQ_t* convertBinaryTree2BST(nodeQ_t* binTreeRoot){
    int size;
    nodeQ_t* temp;
    size = calSize(binTreeRoot);
    bintreetoarr(binTreeRoot);
    selectionSort(treeArray, size);
    temp = createBST(binTreeRoot);
    return temp;  
    
}
nodeQ_t* flipBST(nodeQ_t* bstRoot){
    if(EMPTYNODE== bstRoot) 
    return bstRoot;
    
    else{
        nodeQ_t* a;

        flipBST(bstRoot->left);
        
        flipBST(bstRoot->right);

        a = bstRoot->left;

        bstRoot->left = bstRoot->right;
        
        bstRoot->right = a;
    }

    return bstRoot;
}
nodeQ_t* mergeTwoBSTs(nodeQ_t* bst1Root, nodeQ_t* bst2Root){
    short m = cn(bst1Root);
    short n = cn(bst2Root);
    short* Arr1 = (short*)malloc(sizeof(short)*m);
    short a=0;
    i(bst1Root,Arr1,&a);

    short* Arr2 = (short*)malloc(sizeof(short)*n);
    short d=0;
    i(bst2Root,Arr2,&d);

    short* Arr = mrg(Arr1,Arr2,m,n);

    return sab ( Arr,0, m+n-1);
}
