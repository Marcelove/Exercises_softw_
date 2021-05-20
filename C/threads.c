#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* myturn(void * arg) {

        int a = *arg;
    
        for(int a = 0; a < 7; a++)
        {
                sleep(1);
                printf("My turn %d!\n", a);

        }

        return NULL;
}

void yourturn() {

        for(int a = 0; a < 5; a++)
        {
                sleep(2);
                printf("Your turn %d!\n", a);
        }
}

int main() {

        pthread_t newthread;

        int a = 1;

        pthread_create(&newthread, NULL, myturn(&a), NULL);
        //myturn();
        yourturn();

        pthread_join(newthread, NULL); //Guarantees thread is going to finish

}

//gcc -pthread -o main c.c
