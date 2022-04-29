#include "csl102_th2.h"
#include <stdlib.h>


void insertElement(nodeQ_t** root, short itm){
    nodeQ_t* temp = (nodeQ_t*)malloc(sizeof(nodeQ_t));
    nodeQ_t* ptr = (nodeQ_t*)malloc(sizeof(nodeQ_t));
    temp->data = itm;
    temp->next = EMPTYNODE;
    if(*root == EMPTYNODE){
        *root = temp;
    }
    else{
        ptr = *root;
        while(ptr->next != EMPTYNODE){
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}



void move_node(nodeQ_t** dRef, nodeQ_t** sRef){
    if(*sRef == EMPTYNODE){
        return ;
    }
    nodeQ_t* newNode = *sRef;
    *sRef = (*sRef)->next;
    newNode->next = *dRef;
    *dRef = newNode;
}

int get_count(nodeQ_t* head){
    nodeQ_t* current = head;
    int count = 0;
    while(current != EMPTYNODE){
        count++;
        current = current->next;
    }
    return count;
}
nodeQ_t* getIntersectionNode(int d, nodeQ_t* head1, nodeQ_t* head2){
    nodeQ_t* current1 = head1;
    nodeQ_t* current2 = head2;
    for(int i = 0; i < d; i++){
        if(current1 == EMPTYNODE){
            return EMPTYNODE;
        }
        current1 = current1->next;

    }
    while(current1 != EMPTYNODE && current2 != EMPTYNODE){
        if(current1 == current2){
        
            return current1;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return EMPTYNODE;
}


nodeQ_t* createList(short values[], short sz){
    
    nodeQ_t* head = EMPTYNODE;
    
    for(int i = 0; i < sz; i++){
        insertElement(&head, values[i]);
    }
    return head;
}


status_t deleteNodes(nodeQ_t* head, nodeQ_t** out_newHead, short in_data){
    if(EMPTYNODE == head) return LIST_FALSE;
    int count = 0;
    nodeQ_t* temp = head, *prev;
    
    while(temp != EMPTYNODE && temp->data == in_data){
        *out_newHead = temp->next;
        free(temp);
        temp = *out_newHead;
    }

    while(temp->next != EMPTYNODE){
        if(temp->next->data == in_data)
            {
                temp->next = temp->next->next;
                count++;
            }
            else
            {
                temp = temp->next;    
            }

    }
    if(count > 0){
        return LIST_TRUE;
    }
    else{
        return LIST_FALSE;
    }
}


status_t splitLists(nodeQ_t* head, nodeQ_t** out_evenList, nodeQ_t** out_oddList){
    if(head == EMPTYNODE){
        return LIST_FALSE;
    }
    nodeQ_t aDummy;
    nodeQ_t* aTail = &aDummy;               // points to the last node in `a`
    aDummy.next = EMPTYNODE;
 
    nodeQ_t bDummy;
    nodeQ_t* bTail = &bDummy;               // points to the last node in `b`
    bDummy.next = EMPTYNODE;
 
    nodeQ_t* current = head;
 
    while (current != EMPTYNODE)
    {
        move_node(&(aTail->next), &current);     // add at `a` tail
        aTail = aTail->next;                    // advance the `a` tail
        if (current != NULL)
        {
            move_node(&(bTail->next), &current);
            bTail = bTail->next;
        }
    }
    *out_evenList = aDummy.next;
    *out_oddList = bDummy.next;
    return LIST_TRUE;

}
status_t getCommonSubList(nodeQ_t* head1, nodeQ_t* head2, nodeQ_t** out_commonSubList){
        
        if(head1 == EMPTYNODE || head2 == EMPTYNODE)
        {
            return LIST_FALSE;
        }
        int flag = 0;
        nodeQ_t* temp;
        while(head1 != EMPTYNODE)
        {
            temp = head2;
            while(temp != EMPTYNODE)
            {
                if(head1 == temp)
                {
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }
            
            if(flag==1)
            {
                *out_commonSubList = head1;
                return LIST_TRUE;
            }
            head1 = head1->next;
        }
        return LIST_FALSE;

}



