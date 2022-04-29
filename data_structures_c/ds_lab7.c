#include "csl102_lab7.h"
#include <stdlib.h>
#include <stdio.h>

void delete(nodeQ_t** head, nodeQ_t* del){
    if((*head) == del){
        (*head) = del->next;
    }

    if(del->next != EMPTYNODE){
        del->next->prev = del->prev;
    }

    if(del->prev != EMPTYNODE){
        del->prev->next = del->next;
    }

    free(del);
}

nodeQ_t* createNode(short values[4]){
    nodeQ_t* cnode;
    cnode = (nodeQ_t*)malloc(sizeof(nodeQ_t));
    for(int i = 0; i < 4; i++){
        cnode->data[i] = values[i];
    }
    cnode->prev = EMPTYNODE;
    cnode->next = EMPTYNODE;
    return cnode;

}


status_t appendNode(nodeQ_t* head, nodeQ_t* newNode){
    if(head == EMPTYNODE || newNode == EMPTYNODE){
        return LIST_FALSE;
    }
    while(head != EMPTYNODE){
        if(head->next == EMPTYNODE){
            head->next = newNode;
            newNode->prev = head;
            return LIST_TRUE;
        }
        head = head->next;
    }
    return LIST_FALSE;

}


status_t prependNode(nodeQ_t* head, nodeQ_t* newNode){
    if(head == EMPTYNODE || newNode == EMPTYNODE){
        return LIST_FALSE;
    }
    
    newNode->next = head;
    newNode->prev = EMPTYNODE;
    head->prev = newNode;
    head = newNode;
    
    return LIST_TRUE;
}

status_t deleteNode(nodeQ_t* head, nodeQ_t** out_newHead, short value){
    if(head == EMPTYNODE){
        return LIST_FALSE;
    }
    int flag = 0;

    nodeQ_t* current = head;
    nodeQ_t* next;

    while(current != EMPTYNODE){

        if(current->data[0] == value || current->data[1] == value || current->data[2] == value || current->data[3] == value){
            next = current->next;

            delete(&head, current);

            current = next;
            flag = 1;
        }
        else{
            current = current->next;
        }

        
    }
    *out_newHead = head;
    if(flag == 1){
        return LIST_TRUE;
    }
    else{
        return LIST_FALSE;
    }

    
}
