#include "csl210_lab2a.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//short arr[10000] = {0};
short inarr[10000] = {0};
short prearr[10000] = {0};
short postarr[10000] = {0};
int i = 0, j = 0, k = 0;
quadNode_t* createQuadNode(short val){
    quadNode_t* node = (quadNode_t*)malloc(sizeof(quadNode_t));
    node->value = val;
    node->child0 = EMPTYNODE;
    node->child1 = EMPTYNODE;
    node->child2 = EMPTYNODE;
    node->child3 = EMPTYNODE;
    return node;
}
int minflag = 0;
int maxflag = 0;
quadNode_t* getParent(quadNode_t* root, short val){
    while(root != EMPTYNODE){
        if((val < root->value) && (root->child0 == EMPTYNODE)){
            return root;
        }
        else if((val < root->value) && (root->child0 != EMPTYNODE)){
            root = root->child0;
        }
        else if((val > root->value) && (root->child2 != EMPTYNODE)){
            root = root->child2;
        } 
        else if((val > root->value) && (root->child2 == EMPTYNODE)){
            return root;
        }
        else {
            return EMPTYNODE;
        }

    }
    return EMPTYNODE;
}
void insertQuadNode(quadNode_t* root, quadNode_t* newNode){
    //printf("Insert : %d \n", root->value);
    if(root == EMPTYNODE || newNode == EMPTYNODE){
        return;
    }
    quadNode_t* parent = getParent(root, newNode->value);
    if(parent == EMPTYNODE){
        return;
    }
    if(newNode->value > parent->value){
        parent->child2 = newNode;
        //parent = parent->child2;
    }
    if(newNode->value < parent->value){
        parent->child0 = newNode;
        //parent = parent->child0;
    }
    /*
    if(root != EMPTYNODE){
        printf("quad node : %d \n", root->value);
    }
    //printf("quad node : %d \n", root->value);
    //printf("new node value : %d \n", newNode->value);
    if(root == EMPTYNODE){
        root = newNode;
        printf("root is updated to %d \n", root->value);
    }
    else if(newNode->value <= root->value){
        if(root->child0 != EMPTYNODE && root->child1 != EMPTYNODE){
            if(minflag == 0){
                insertQuadNode(root->child0, newNode);
                minflag = 1;
            }
            else if(minflag == 1){
                insertQuadNode(root->child1, newNode);
                minflag = 0;
            }
        }
        else if(root->child0 == EMPTYNODE && root->child1 == EMPTYNODE){
            root->child0 = newNode;
            root = root->child0;
        }
        else if(root->child0 != EMPTYNODE && root->child1 == EMPTYNODE){
            root->child1 = newNode;
            root = root->child1;
        }
        else if(root->child0 == EMPTYNODE && root->child1 != EMPTYNODE){
            root->child0 = newNode;
            root = root->child0;
        }
    }
    else{
        if(root->child2 != EMPTYNODE && root->child3 != EMPTYNODE){
            if(maxflag == 0){
                insertQuadNode(root->child2, newNode);
                maxflag = 1;
            }
            else if(maxflag == 1){
                insertQuadNode(root->child3, newNode);
                minflag = 0;
            }
        }
        else if(root->child2 == EMPTYNODE && root->child3 == EMPTYNODE){
            root->child2 = newNode;
            root = root->child2;
        }
        else if(root->child3 != EMPTYNODE && root->child3 == EMPTYNODE){
            root->child3 = newNode;
            root = root->child3;
        }
        else if(root->child2 == EMPTYNODE && root->child3 != EMPTYNODE){
            root->child2 = newNode;
            root = root->child2;    
        }
    }
    */
}
bstNode_t* createBstNode(short val){
    bstNode_t* node = (bstNode_t*)malloc(sizeof(bstNode_t));
    node->value = val;
    node->right = EMPTYNODE;
    node->left = EMPTYNODE;
    return node;
}
void getInorder(bstNode_t* root){
    //int i = 0;
    if(root == EMPTYNODE){
        return;
    }
    //quadNode_t* temp = qroot;
    getInorder(root->left);
    //insertQuadNode(temp, createQuadNode(root->value));
    inarr[i++] = root->value;
    getInorder(root->right);
}
void getPreorder(bstNode_t* root){
    if(root == EMPTYNODE){
        return;
    }
    //quadNode_t* temp = qroot;
    //printf("Inside preorder : %d \n", root->value);
    //printf("qroot value : %d\n", temp->value);
    //insertQuadNode(qroot, createQuadNode(root->value));
    prearr[j++] = root->value;
    getPreorder(root->left);
    getPreorder(root->right);
}
void getPostorder(bstNode_t* root){
    int i = 0;
    if(root == EMPTYNODE){
        return;
    }
    //quadNode_t* temp = qroot;
    getPostorder(root->left);
    getPostorder(root->right);
    //insertQuadNode(temp, createQuadNode(root->value));
    postarr[k++] = root->value;
}

quadNode_t* convertBST2QuadTree(bstNode_t* rootBST, traversal_t order){
    bstNode_t* temp = rootBST;
    //quadNode_t* qroot = EMPTYNODE;
    int idx = 0;
    quadNode_t* quadroot;
    if(order == 0){
        //printf("Inorder\n");
        getInorder(temp);
        quadroot = createQuadNode(inarr[0]);
        idx++;
        while(inarr[idx] !=0){
            //printf("contents of inarr : %d \n", inarr[idx]);
            insertQuadNode(quadroot, createQuadNode(inarr[idx++]));
        }
    }
    else if(order == 1){
        getPreorder(temp);
        quadroot = createQuadNode(prearr[0]);
        idx++;
        while(prearr[idx] != 0){
            //printf("contents of prearr : %d \n", prearr[idx]);
            insertQuadNode(quadroot, createQuadNode(prearr[idx++]));
        }
    }
    else if(order == 2){
        getPostorder(temp);
        quadroot = createQuadNode(postarr[0]);
        idx++;
        while(postarr[idx] != 0){
            //printf("contents of post arr : %d \n", postarr[idx]);
            insertQuadNode(quadroot, createQuadNode(postarr[idx++]));
        }
    }
    //printf("qroott val : %d \n", quadroot->value);
    return quadroot;

}
