/*
 * Name: Tiffany Nguyen
 * gpel: ssh gpel13.cs.nor.ou.edu -l nguy0850
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *add_thread(void *vargp);

int total = 0;        // total sum
pthread_mutex_t lock; // used to maintain synchronization of threads

int main()
{
    pthread_t threads[10];                                // array of 10 threads
    int thread_args[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // array of 10 indexes for the threads

    // creates 10 threads
    for (int t = 0; t < 10; t++)
    {
        pthread_create(&threads[t], NULL, add_thread, &thread_args[t]);
    }

    // Wait for all threads to finish
    for (int t = 0; t < 10; t++)
    {
        pthread_join(threads[t], NULL);
    }

    printf("final total is %d\n", total); // prints the final total

    return 0;
}

// function to add the threads
void *add_thread(void *vargp)
{
    int index = *(int *)vargp; // get the index from the argument
    int sum = 0;               // local sum
    int MAX_NUM = 1000;        // 1000 for each thread

    // adds the specific values from 0-9999 to the local sum
    for (int i = MAX_NUM * index; i < MAX_NUM * (index + 1); ++i)
    {
        sum += i;
    }

    pthread_mutex_lock(&lock); // locks mutex; prevents other threads from accessing total at the same time

    total += sum; // adds the sum to the total
    printf("process %d total is %d \n", index, total);

    pthread_mutex_unlock(&lock); // unlocks the mutex; allows changes to total from another thread
    return NULL;
}
