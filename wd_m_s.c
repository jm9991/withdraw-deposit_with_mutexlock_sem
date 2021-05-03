#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_THREAD_DEPOSIT 7
#define MAX_THREAD_WITHDRAW 3 
double amount =0;
int withdraw_input;
int deposit_input;
// the mutex identifier
pthread_mutex_t mutex;

sem_t sem;

//withdraw function
void* withdraw(){
printf("Executing withdraw function");
printf("\n");
sem_wait(&sem); //decrementing semaphore
pthread_mutex_lock(&mutex);
amount = amount - withdraw_input;
printf("Amount after withdrawal = %.2f",amount);
printf("\n");
pthread_mutex_unlock(&mutex);
}

//deposit function 
void* deposit(){
printf("Executing deposit function");
printf("\n");
sem_post(&sem); //incrementing semaphore
pthread_mutex_lock(&mutex);
amount = amount + deposit_input;
printf("Amount after deposit = %.2f",amount);
printf("\n");
pthread_mutex_unlock(&mutex);

}

int main(int argc, char *argv[]){
if (argc !=3)
{
    printf("usage: a.out <deposit integer value> <withdraw integer value> \n");
    return -1;
}

if (atoi(argv[1]) !=100 )
{
    printf("%d must be 100 \n", atoi(argv[1]));
}
deposit_input=100;
        
if (atoi(argv[2]) !=100)
{
    printf("%d must be 100 \n", atoi(argv[2]));
}
withdraw_input=100;

    
    
    // the thread identifier
    pthread_t threads_withdraw[MAX_THREAD_WITHDRAW];
    pthread_t threads_deposit[MAX_THREAD_DEPOSIT]; 
    
    
    if (sem_init(&sem, 0, 0) !=0)
    {
        printf("Error in initializing semaphore \n");
    }

    if (pthread_mutex_init(&mutex,NULL) !=0)
    {
        printf("Error in initializing mutex \n");
    }
    

    for (int i = 0; i < MAX_THREAD_DEPOSIT; i++)
		{
            if(pthread_create(&threads_deposit[i], NULL, deposit, (void*)NULL)!=0)
            printf("Error in Deposit Thread %d \n", i);
        }
    for (int i = 0; i < MAX_THREAD_WITHDRAW; i++)
		{
            if(pthread_create(&threads_withdraw[i], NULL, withdraw, (void*)NULL)!=0)
            printf("Error in Withdraw Thread %d \n", i);
        }

    //joins the threads 
    for (int i = 0; i < MAX_THREAD_DEPOSIT; i++) 
		{
            pthread_join(threads_deposit[i], NULL); 
        }
    for (int i = 0; i < MAX_THREAD_WITHDRAW; i++) 
		{
            pthread_join(threads_withdraw[i], NULL); 
        }

    
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
    printf("Final amount = %.2f",amount);
    printf("\n");
    return 0;

}

