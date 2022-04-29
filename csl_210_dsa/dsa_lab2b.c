#include "csl210_lab2b.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

btNode_t* createNode(short value){
    btNode_t* node = (btNode_t*)malloc(sizeof(btNode_t));
    node->value = value;
    node->right = EMPTYNODE;
    node->left = EMPTYNODE;
    return node;
}

int check(btNode_t* node, int min, int max)
{
  if (node==EMPTYNODE)
     return 1;

  if (node->value < min || node->value > max)
     return 0;
  return check(node->left, min, node->value-1) && check(node->right, node->value+1, max);  
}

int checkBST(btNode_t* node)
{
    btNode_t* temp = node;
    //printf("Inside checkbst ");
    //printf("%d \n", node->value);
  return(check(temp, INT_MIN, INT_MAX));
}
//btNode_t* ret;
btNode_t* dfs(btNode_t* node, btNode_t** ret, int* flag){
    //btNode_t* ret;
    if(node == EMPTYNODE){
        return EMPTYNODE;
    }
    //printf("pos 2 %d \n", node->value);
    btNode_t* temp = node;
    if(checkBST(temp) && temp->left != EMPTYNODE && temp->right != EMPTYNODE){
        //printf("pos1 %d \n", temp->value);
        *flag = 1;
        *ret = temp;
    }
    dfs(node->left, ret, flag);
    dfs(node->right, ret, flag);
    //printf("Value if ret : %d ", ret->value);
    return *ret;
}


btNode_t* getBSTSubtree(btNode_t* rootNode){
    btNode_t* temp = rootNode;
    btNode_t* ret;
    int flag;
    flag = 0;
    btNode_t* res = dfs(temp, &ret, &flag);
    //printf("res val : %d ", res->value);
    //printf("ret val : %d ", ret->value);
    if(flag == 0){
        return EMPTYNODE;
    }
    return ret;
}
