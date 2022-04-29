#include "csl210_lab1.h"
#include <stdlib.h>
#include <stdio.h>
nodeQ_t* createNode(unsigned short val, unsigned short r, unsigned short c){
    nodeQ_t* ptr = (nodeQ_t*)malloc(sizeof(nodeQ_t));
    ptr->row = r;
    ptr->column = c;
    ptr->value = val;
    ptr->next = EMPTYNODE; // NULL
    return ptr;
}
priorityNodeQ_t* createpn(unsigned short value, unsigned short priority){
    priorityNodeQ_t* ptr = (priorityNodeQ_t*)malloc(sizeof(priorityNodeQ_t));
    ptr->value = value;
    ptr->priority = priority;
    ptr->next = EMPTYNODE;
    return ptr;
}
nodeQ_t* convertSparseMatrixToLinkedList(unsigned short** matrix, unsigned short rows, unsigned short columns){
    unsigned short iset = 77;
    nodeQ_t* headi = createNode(iset, rows, columns);
    nodeQ_t* res;
    nodeQ_t* head;
    res = headi;
    
    int count = 0;
    
    for(unsigned short i = 0; i < rows; i++){
        for(unsigned short j = 0; j < columns; j++){
            
            unsigned short x = 0;
            if(matrix[i][j] != x){
                count++;
                if(count == 1){
                    head = createNode(matrix[i][j], i, j);
                    headi->next = head;
                    
                    
                }
                else{
                    nodeQ_t* c = createNode(matrix[i][j], i, j);
                    head->next = c;
                    head = head->next;
                }
            }
            
        }
    }
    return res;
}
nodeQ_t* searchinl2(nodeQ_t* l1, nodeQ_t* l2){
    while(l2){
        if(l1->column == l2->row){
            return createNode((l1->value)*(l2->value), l1->row, l2->column);
        }
        l2 = l2->next;
    }
    return EMPTYNODE;
}

nodeQ_t* multiplySparseMatricesLinkedLists(nodeQ_t* matrix_llist_1, nodeQ_t* matrix_llist_2){
    unsigned short set = 100;
    nodeQ_t* head = createNode(set, matrix_llist_1->row, matrix_llist_2->column);
    nodeQ_t* curr;
    int count = 0;
    
    matrix_llist_1 = matrix_llist_1->next;
    matrix_llist_2 = matrix_llist_2->next;
    while(matrix_llist_1){
        
        nodeQ_t * t = searchinl2(matrix_llist_1, matrix_llist_2);
        if(t != EMPTYNODE){
            count++;
            if(count == 1){
                curr = t;
                head->next = curr;
                
                
            }
            else{
                
                curr->next = t;
                
                curr = curr->next;
            }
        }

        matrix_llist_1 = matrix_llist_1->next;
    }
    nodeQ_t* templ = head;
    nodeQ_t* temp = templ;
    
    unsigned short **temparr = (unsigned short **)malloc(templ->row*sizeof(unsigned short *));
    for(int r = 0; r < templ->row; r++){
        temparr[r] = (unsigned short *)malloc(templ->column*sizeof(unsigned short));
    }
    unsigned short defval = 0;
    
    for(int i = 0; i < templ->row; i++){
        for(int j = 0; j < templ->column; j++){
            temparr[i][j] = defval;
    
        }
    }
    templ = templ->next;
    while(templ){
        if(temparr[templ->row][templ->column] != 0){
            temparr[templ->row][templ->column] += templ->value;
        }
        else{
            temparr[templ->row][templ->column] = templ->value;
        }
    
        templ = templ->next;
    }
    nodeQ_t* ret = convertSparseMatrixToLinkedList(temparr, head->row, head->column);

    return ret;
}

void insertPriorityHashTable(priorityNodeQ_t* item){
    unsigned short hashedkey = hashFuncLab1(item->value);
    priorityNodeQ_t* head;
    if(EMPTYNODE == g_priorityHashTable[hashedkey]){
        g_priorityHashTable[hashedkey] = item;
        return;
    }
    head = g_priorityHashTable[hashedkey];
    if(item->priority <= head->priority){
        g_priorityHashTable[hashedkey] = item;
        item->next = head;
        return;
    }
    while(head){
        if(item->priority > head->priority){
            if(head->next){
                if(item->priority <= head->next->priority){
                    item->next = head->next;
                    head->next = item;
                    return;
                }
                else{
                    head = head->next;
                }
            }
            else{
                head->next = item;
                return;
            }
        }
    }
    
}

priorityNodeQ_t* dequeueFromPriorityHashTable(unsigned short key){
    int hashedkey = hashFuncLab1(key);
    priorityNodeQ_t* head = g_priorityHashTable[hashedkey];
    if(head == EMPTYNODE){
        return EMPTYNODE;
    }
    if(head->next != EMPTYNODE){
        g_priorityHashTable[hashedkey] = head->next;
    }
    else{
        g_priorityHashTable[hashedkey] = EMPTYNODE;
    }
    return head;

}

int main()
{
    /*
    int row = 3, col = 3;
    unsigned short **arr = (unsigned short **)malloc(row*sizeof(unsigned short *));
    for(int r = 0; r < row; r++){
        arr[r] = (unsigned short *)malloc(col*sizeof(unsigned short));
    }
    unsigned short d = 0;
    unsigned short a = 7;
    unsigned short b = 9;
    arr[0][0] = d;
    arr[0][1] = b;
    arr[0][2] = d;
    arr[1][0] = d;
    arr[1][1] = a;
    arr[1][2] = d;
    arr[2][0] = b;
    arr[2][1] = a;
    arr[2][2] = d;
    nodeQ_t* n = convertSparseMatrixToLinkedList(arr, 3, 3);
    printf("in main1st\n");
    //printf("res value : %d\n", n->value);
    //printf("in main\n");
    //printf("%d\n", n->value);
    //printf("%d\n", n->next->value);
    //printf("%d\n", n->next->next->value);
    
    while(n != EMPTYNODE){
        //printf("in while\n");
        printf("row: %d\t", n->row);
        printf("column: %d\t", n->column);
        printf("value: %d\t", n->value);
        printf("\n");
        n = n->next;
    }
    printf("multipy matrix funciton\n");
    unsigned short **arr1 = (unsigned short **)malloc(row*sizeof(unsigned short *));
    for(int r = 0; r < row; r++){
        arr1[r] = (unsigned short *)malloc(col*sizeof(unsigned short));
    }
    unsigned short **arr2 = (unsigned short **)malloc(row*sizeof(unsigned short *));
    for(int r = 0; r < row; r++){
        arr2[r] = (unsigned short *)malloc(col*sizeof(unsigned short));
    }
    unsigned short aa = 1, bb = 2, cc = 3, dd = 4;
    arr1[0][0] = d;
    arr1[0][1] = aa;
    arr1[0][2] = d;
    arr1[1][0] = bb;
    arr1[1][1] = d;
    arr1[1][2] = dd;
    arr1[2][0] = d;
    arr1[2][1] = cc;
    arr1[2][2] = d;

    arr2[0][0] = d;
    arr2[0][1] = d;
    arr2[0][2] = aa;
    arr2[1][0] = d;
    arr2[1][1] = bb;
    arr2[1][2] = d;
    arr2[2][0] = d;
    arr2[2][1] = d;
    arr2[2][2] = cc;
    nodeQ_t* list1 = convertSparseMatrixToLinkedList(arr1, 3, 3);
    nodeQ_t* list2 = convertSparseMatrixToLinkedList(arr2, 3, 3);
    nodeQ_t* ll2 = list2;
    //printf("here\n");
    nodeQ_t* product = multiplySparseMatricesLinkedLists(list1, list2);
    
    printf("list 1\n");
    while(list1 != EMPTYNODE){
        //printf("in while\n");
        printf("row: %d\t", list1->row);
        printf("column: %d\t", list1->column);
        printf("value: %d\t", list1->value);
        printf("\n");
        list1 = list1->next;
    }
    printf("list 2\n");
    while(ll2 != EMPTYNODE){
        //printf("in while\n");
        printf("row: %d\t", ll2->row);
        printf("column: %d\t", ll2->column);
        printf("value: %d\t", ll2->value);
        printf("\n");
        ll2 = ll2->next;
    }
    
    
    printf("product matrix \n");
    while(product != EMPTYNODE){
        //printf("in while\n");
        printf("row: %d\t", product->row);
        printf("column: %d\t", product->column);
        printf("value: %d\t", product->value);
        printf("\n");
        product = product->next;
    }


    
    printf("hash table insert function \n");
    insertPriorityHashTable(createpn(46, 3));//1
    insertPriorityHashTable(createpn(44, 1));//4
    insertPriorityHashTable(createpn(56, 4));//1
    insertPriorityHashTable(createpn(66, 2));//1
    insertPriorityHashTable(createpn(34, 3));//4
    printf("value: %d priority: %d\n", g_priorityHashTable[1]->value, g_priorityHashTable[1]->priority);
    printf("value: %d priority: %d\n", g_priorityHashTable[1]->next->value, g_priorityHashTable[1]->next->priority);
    printf("value: %d priority: %d\n", g_priorityHashTable[4]->value, g_priorityHashTable[4]->priority);
    printf("value: %d priority: %d\n", g_priorityHashTable[4]->next->value, g_priorityHashTable[4]->next->priority);
    printf("hash table dequeue function\n");
    unsigned short a1 = 1;
    unsigned short a2 = 4;
    unsigned short a3 = 3;
    priorityNodeQ_t* n1 = dequeueFromPriorityHashTable(a1);
    priorityNodeQ_t* n2 = dequeueFromPriorityHashTable(a2);
    priorityNodeQ_t* n3 = dequeueFromPriorityHashTable(a3);
    if(n3 != EMPTYNODE){
        printf("dequed value: %d dequeud priority: %d\n",n3->value,n3->priority);
    }
    printf("dequed value: %d dequeud priority: %d\n",n1->value,n1->priority);
    printf("dequed value: %d dequeud priority: %d\n",n2->value,n2->priority);
    printf("value: %d priority: %d\n", g_priorityHashTable[1]->value, g_priorityHashTable[1]->priority);
    printf("value: %d priority: %d\n", g_priorityHashTable[1]->next->value, g_priorityHashTable[1]->next->priority);
    printf("value: %d priority: %d\n", g_priorityHashTable[4]->value, g_priorityHashTable[4]->priority);
    //printf("value: %d priority: %d\n", g_priorityHashTable[4]->next->value, g_priorityHashTable[4]->next->priority);
    */
    return 0;
}