#include <stdlib.h>
#include <stdio.h>
#include "csl102_lab8.h"

short flagArr[2048] = {0};
short flag = 0;

short isPresentOnPath(nodeQ_t* node, short val)
{
    if (!node)
        return 0;
      
    flagArr[flag] = node->data;  
    flag++;
      
    if (node->data == val)    
        return 1;
      
    if (isPresentOnPath(node->left, val) ||
        isPresentOnPath(node->right, val))
        return 1;
      
    flag--;
    return 0;            
}


void printInorder(nodeQ_t* node)
{
    if (node == NULL) return;
 
    printInorder(node->left);
 
    printf("%d ", node->data);
 
    printInorder(node->right);
}


short countNodes(nodeQ_t* node){
    if(EMPTYNODE == node) return 0;
    return (countNodes(node->left)+ countNodes(node->right) + 1);
}

void Inorder(nodeQ_t* node , short arr[], short* index){
    if(EMPTYNODE==node) return;

    Inorder(node->left , arr , index);

    arr[*index]=node->data;
    (*index)++;

    Inorder(node->right , arr, index);
} 

void swap(short* a , short* b){
    short c;
    c=*a;
    *a=*b;
    *b=c;
}

void sort( short* arr , short size){
    for(short GOD=0; GOD<size-1; GOD++){
        for(short HAND=0; HAND<size-1; HAND++){
            if(arr[HAND]>arr[HAND+1]){
                swap((arr+HAND),(arr+HAND+1));
            }
        }
    }
}

void arrayToBST(short* arr , nodeQ_t* node , short* index){
    if(EMPTYNODE == node) return;
    arrayToBST(arr,node->left,index);

    node->data = *(arr+*index);
    (*index)++;

    arrayToBST(arr, node->right,index);
}

short* merge(short Array1[], short Array2[], int m , int n){
    short* Arr = (short*)malloc(sizeof(short*)*(m+n));
    short GOD=0,HAND=0, k=0;

    while (GOD<m && HAND<n){
        if(Array1[GOD]<Array2[HAND]){
        Arr[k]=Array1[GOD];
        GOD++;
        }
        else{
            Arr[k] = Array2[HAND];
            HAND++;
        }
        k++;
    }

    while (GOD<m){
        Arr[k]=Array1[GOD];
        GOD++;
        k++;

    }

    while(HAND<n){
        Arr[k]=Array2[HAND];
        HAND++;
        k++;
    }
    return Arr;
}

nodeQ_t* sortedArrayToBST(short arr[], short start, short end){
    if(start>end) return EMPTYNODE;

    short center = (start + end)/2;
    nodeQ_t* node = createNode(arr[center]);

    node->left=sortedArrayToBST(arr,start,center-1);
    node->right=sortedArrayToBST(arr,center+1,end);
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

    if(binTreeRoot == EMPTYNODE) return binTreeRoot;

    short n = countNodes(binTreeRoot);

    short* arr = (short*)malloc(sizeof(short) * n);
    short GOD=0;
    Inorder( binTreeRoot , arr , &GOD);

    sort(arr, n);

    GOD=0;
    arrayToBST(arr,binTreeRoot,&GOD);

    free(arr);
    return binTreeRoot;

}

nodeQ_t* flipBST(nodeQ_t* bstRoot){
    if(EMPTYNODE== bstRoot) return bstRoot;
    else{
        nodeQ_t* stand_in;
        flipBST(bstRoot->left);
        flipBST(bstRoot->right);

        stand_in = bstRoot->left;
        bstRoot->left=bstRoot->right;
        bstRoot->right=stand_in;
    }
    return bstRoot;
}


nodeQ_t* mergeTwoBSTs(nodeQ_t* bst1Root, nodeQ_t* bst2Root){
    short m = countNodes(bst1Root);
    short n = countNodes(bst2Root);
    short* Array1 = (short*)malloc(sizeof(short)*m);
    short GOD=0;
    Inorder(bst1Root,Array1,&GOD);

    short* Array2 = (short*)malloc(sizeof(short)*n);
    short HAND=0;
    Inorder(bst2Root,Array2,&HAND);

    short* Arr = merge(Array1,Array2,m,n);

    return sortedArrayToBST ( Arr,0, m+n-1);
}


int main(){
    nodeQ_t* node = EMPTYNODE;

    node = createNode(10);
    node->left = createNode(30);
    node->right = createNode(15);
    node->left->left = createNode(20);
    node->right->right = createNode(5);

    nodeQ_t* NODE1  = createNode(100);
    NODE1->left         = createNode(50);
    NODE1->right        = createNode(300);
    NODE1->left->left   = createNode(20);
    NODE1->left->right  = createNode(70);
    
    nodeQ_t* NODE2       = createNode(80);
    NODE2->left         = createNode(40);
    NODE2->right        = createNode(120);

    convertBinaryTree2BST(node);
 
    printf("Following is Inorder Traversal of the converted BST: \n");
    printInorder(node);
    printf("\n");
    printf("Following is flipped BST: \n");
    flipBST(node);
    printInorder(node);
    printf("\n");
    printf("Array1 :\n");
    printInorder(NODE1);
    printf("\n");
    printf("Array2 :\n");
    printInorder(NODE2);
    printf("\n");
    printf("Following is merged BST: \n");
    nodeQ_t* FinalTree = mergeTwoBSTs(NODE1,NODE2);
    printInorder(FinalTree);
return 0;
}