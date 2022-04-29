#include "csl102_lab6.h"
#include <stdio.h>

int main()
{
    nodeQ_t* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    nodeQ_t* node1 = root;
    nodeQ_t* node2 = root;
    short* ptrArr1;
    short* ptrArr2;
    short preidx;
    short* ptrArr;
    short idx;
    short postidx;
    getInorder(root, &ptrArr, &idx);
    printf("size of arr = %d\n", idx);
    for(int i = 0; i < idx; i++){
        printf("%d->", ptrArr[i]);
    }

    getPreorder(node1, &ptrArr1, &preidx);
    printf("\nsize of pre arr = %d\n", preidx);
    for(int i = 0; i < preidx; i++){
        printf("%d->", ptrArr1[i]);
    }

    getPostorder(node2, &ptrArr2, &postidx);
    printf("\nsize of post arr = %d\n", postidx);
    for(int i = 0; i < postidx; i++){
        printf("%d->", ptrArr2[i]);
    }

    return 0;
}