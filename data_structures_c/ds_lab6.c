#include "csl102_lab6.h"
#include "stdlib.h"

#include <stdio.h>



struct stackNode{
    nodeQ_t* t;
    struct stackNode* next;
};
typedef struct stackNode stackQ_t;




struct Stack{
    int size;
    int top;
    nodeQ_t* *array;


};




nodeQ_t* newNode(short data){
    nodeQ_t* node = (nodeQ_t*)malloc(sizeof(nodeQ_t));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}




struct Stack* createStack(int size){
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->size = size;
    stack->top = -1;
    stack->array = (nodeQ_t**)malloc(stack->size * sizeof(nodeQ_t));
    return stack;
}



int isFull(struct Stack* stack)
{
    return stack->top - 1 == stack->size;
}




int isEmptyS(struct Stack* stack)
{
    return stack->top == -1;
}




void pushS(struct Stack* stack, nodeQ_t* node)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = node;
}




nodeQ_t* popS(struct Stack* stack)
{
    if (isEmptyS(stack))
        return NULL;
    return stack->array[stack->top--];
}
  




int isEmpty(stackQ_t* top){
    return (top == NULL)? 1: 0;
}





nodeQ_t* createNode(short data)
{
	nodeQ_t* node = (nodeQ_t*)malloc(sizeof(nodeQ_t));
	node->data = data;

	node->left = NULL;
	node->right = NULL;
	return node;
}





void push(stackQ_t** t_ref, nodeQ_t* t){
    stackQ_t* new_tnode = (stackQ_t*)malloc(sizeof(stackQ_t));

    new_tnode->t = t;
    new_tnode->next = (*t_ref);
    (*t_ref) = new_tnode;
}





nodeQ_t* pop(stackQ_t** top_ref){
    nodeQ_t* res;
    stackQ_t* top;
    
    top = *top_ref;
        res = top->t;
        *top_ref = top->next;
        free(top);
        return res;

}




void getInorder(nodeQ_t* node, short **out_array, short *out_size){

    nodeQ_t* current = node;
    stackQ_t* s = NULL;
    int flag = 0;
    int i = 0;
    short count = 0;
    short outArr[2048] = {0};

    while(flag == 0){

        if(current != NULL){
            push(&s, current);
            current = current->left;
        }
        else{
            if(0 == isEmpty(s)){
                current = pop(&s);
                outArr[i] = current->data;
                i++;    
                current = current->right;
            }
            else{
                flag = 1;
            }


        }
    }

    for(int i = 0; i < 2048; i++){
        
        if(outArr[i] == 0){
            break;
        }
        count++;
    }

    *out_array = outArr;
    
    *out_size = count;

    
}

void getPreorder(nodeQ_t* node, short **out_array, short *out_size){
    stackQ_t* s;
    nodeQ_t* current = node;
    int i = 0;
    int  count = 0;
    int flag = 0;

    
    short preArr[2048] = {0};
    while(flag == 0){
        if(current != NULL){
            preArr[i] = current->data;
            
            
            i++;
            push(&s, current);
            current = current->left;

        }
        else{
            if(0 == isEmpty(s)){
                current = pop(&s);
                //preArr[i] = current->data;
                //printf("else %d\n", preArr[i]);
                //i++;
                current = current->right;
                
            }
            else{
                flag = 1;
            }
        }
    }
    
    for(int i = 0; i < 2048; i++){
        
        if(preArr[i] == 0){
            break;
        }
        count++;
    }
    

    *out_array = preArr;
    
    *out_size = count;
}


void getPostorder(nodeQ_t* node, short **out_array, short *out_size){

    struct Stack* s1 = createStack(3000);
    struct Stack* s2 = createStack(3000);
    short postArr[2048] = {0};
    int i = 0;

    pushS(s1, node);
    nodeQ_t* node1;

    while(!isEmptyS(s1)){
        node1 = popS(s1);
        pushS(s2, node1);
        if(node1->left){
            pushS(s1, node1->left);
        }
        if(node1->right){
            pushS(s1, node1->right);
        }
    }

    while(!isEmptyS(s2)){
        node1 = popS(s2);
        postArr[i] = node1->data;
        i++;
    }

    int count = 0;
    for(int i = 0; i < 2048; i++){
        if(postArr[i] == 0){
            break;
        }
        count++;
    }

    *out_array = postArr;

    *out_size = count;

    

}



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