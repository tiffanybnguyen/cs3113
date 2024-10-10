/*
 * Name: Tiffany Nguyen
 * gpel: ssh gpel13.cs.nor.ou.edu -l nguy0850
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *add_thread(void *vargp);

int total = 0;        // total sum
int counter = 1;      // counter to increment addend
pthread_mutex_t lock; // used to maintain synchronization of threads

int main()
{
    pthread_t threads[10]; // array of 10 threads

    // creates 10 threads
    for (int t = 0; t < 10; t++)
    {
        pthread_create(&threads[t], NULL, add_thread, NULL);
        printf("process %d total is %d and counter is %d\n", t, total, counter); // prints the total and counter for each thread
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
    pthread_mutex_lock(&lock); // locks mutex; prevents other threads from accessing total at the same time

    while (counter < 10000) // increments total while the counter is < 10,000
    {
        total += counter;
        counter++;
    }

    pthread_mutex_unlock(&lock); // unlocks the mutex; allows changes to total from another thread
    return NULL;
}