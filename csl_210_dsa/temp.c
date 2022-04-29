/*
    for(unsigned short i = 0; i < headi->row; i++){
        for(unsigned short j = 0; j < headi->column; j++){
            count++;
            printf("inside for\n");
            if(count == 1){
                if(matrix_llist_1->column == matrix_llist_2->row){
                    head = createNode((matrix_llist_1->value)*(matrix_llist_2->value), matrix_llist_1->row, matrix_llist_2->column);
                    printf("if  row : %d column : %d value : %d ", head->row, head->column, head->value);
                    headi->next = head;
                    //res = headi;
                    //headi->next = head;
                }
            }

            else{
                if(matrix_llist_1->column == matrix_llist_2->row){
                    nodeQ_t* c = createNode((matrix_llist_1->value)*(matrix_llist_2->value), matrix_llist_1->row, matrix_llist_2->column);
                    printf("else  row : %d column : %d value : %d ", c->row, c->column, c->value);
                    head->next = c;
                    head = head->next;
                }
            }

        }
    }
    */