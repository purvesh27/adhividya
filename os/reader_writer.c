#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int count=0,n;
int sem_w=1,sem_r=1,*emp_no;
pthread_t* reader,writer;

void down(int* sem){
    while((*sem)<=0){
    }
    (*sem)--;
}

void up(int* sem){
    (*sem)++;
}


/**
 * @brief function to handle read request by employee
 * 
 * @param ptr function parameters (employee no)
 */
void read_request(void* ptr){
        int index=atoi((char*)ptr);
        down(&sem_r);
        ++count;
        if(1==count){
            down(&sem_w);
        }
        printf("employee %d accessing webpage\n\n",index);
        up(&sem_r);
        sleep(2);
        down(&sem_r);
        printf("employee %d stopped accessing webpage\n\n",index);
        count--;
        if(0==count){
            up(&sem_w);
        }
        up(&sem_r);
        emp_no[(int)index]=0;
}

/**
 * @brief function to handle write request by manager
 * 
 */
void write_request(){
    down(&sem_w);
    down(&sem_r);
    printf("Webpage allocated to manager for writing\n");
    sleep(3);
    printf("Webpage released by the manager\n\n");
    up(&sem_w);
    up(&sem_r);
}


/**
 * @brief Create a reader thread to manage reader request
 * 
 * @param index_str employee number as string
 */
void create_reader(char* index_str){
    int index=atoi(index_str);
    if(!(index<n && index>=0)){
        printf("invalid employee number\n\n");
        return;
    }
    while(1==emp_no[index]){
        printf("employee %d a request already in process please wait or already accessing webpage, cant create multiple request\n\n",index);
        return;
    }
    emp_no[index]=1;
    pthread_create(&reader[index], NULL, (void*)read_request, index_str);
}
/**
 * @brief Create a writer thread to manage write request and wait for it to terminate
 * 
 */
void create_writer(){
    pthread_t writer;
    pthread_create(&writer, NULL, (void*)write_request, NULL);
    pthread_join(writer, NULL);
}

int main(){
    printf("enter the value of n\n");
    scanf("%d",&n);
    reader=(pthread_t*)malloc(n*sizeof(pthread_t));
    emp_no=(int *)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        emp_no[i]=0;
    }
    create_writer();
    create_reader("3");
    create_reader("5");
    create_reader("1");
    create_reader("7");
    create_reader("2");
    create_reader("2");
    create_writer();
    create_reader("7");
    create_reader("1");
    create_reader("4");
    create_reader("7");
    create_writer();
    create_reader("0");
    create_reader("3");
    create_reader("1");
    create_reader("6");
    printf("Here 1\n");
    int i=0;
    while(1){                                      // waiting for all threads to terminate
        pthread_join(reader[i], NULL);
        if(i==n){
            for(int j=0;j<n;j++){
                if(emp_no[j]==1){
                    i=0;
                    continue;
                }
                return 0;
            }
        }
        i++;
    }
    return 0;
}