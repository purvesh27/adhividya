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
