#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#define SEMKEY ((key_t)400L) // semaphore key
// #define NSEMS 1              // number of semaphores being created

pthread_t tid1[1];      /* process id for thread 1 */
pthread_t tid2[1];      /* process id for thread 2 */
pthread_attr_t attr[1]; /* attribute pointer array */

// declaring the three semaphores
sem_t empty;
sem_t full;
sem_t mutex;

char buffer[15];
int in = 0;  // pointers for in location in buffer
int out = 0; // pointers for out location in buffer

void *producer(void *param)
{

    char newChar; // char for character in file
    FILE *fp;     // file pointer for file

    // opens file
    fp = fopen("mytest.dat", "r");

    // loops through the file for each character
    while (fscanf(fp, "%c", &newChar) != EOF)
    {
        sem_wait(&empty); // wait for an empty slot
        sem_wait(&mutex); // ensure mutual exclusion

        // printf("%c", newChar); // replace this with a line that adds the char to the buffer
        buffer[in] = newChar;
        in = (in + 1) % 15;

        sem_post(&mutex); // release mutual exclusion
        sem_post(&full);  // signal that new data is in the buffer
    }

    sem_wait(&empty); // wait for an empty slot
    sem_wait(&mutex); // ensure mutual exclusion

    buffer[in] = '*';
    in = (in + 1) % 15;

    sem_post(&mutex); // release mutual exclusion
    sem_post(&full);  // signal that new data is in the buffer

    fclose(fp);
    pthread_exit(NULL); // idk about this one
}

void *consumer(void *param)
{

    char newChar;

    while (1)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        newChar = buffer[out]; // grabs from the buffer
        out = (out + 1) % 15;

        sem_post(&mutex);
        sem_post(&empty);

        if (newChar == '*') // if reached end of file, then just die
        {
            break;
        }

        printf("%c", newChar); // used to debug
        fflush(stdout);
        sleep(1); // so consumer will run slower than producer
    }
}

int main()
{

    // initialize semaphores
    sem_init(&empty, 0, 15);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    /* Required to schedule thread independently.*/
    pthread_attr_init(&attr[0]);
    pthread_attr_setscope(&attr[0], PTHREAD_SCOPE_SYSTEM);

    // producer and consumer threads
    pthread_create(&tid1[0], &attr[0], producer, NULL);
    pthread_create(&tid2[0], &attr[0], consumer, NULL);

    /* Wait for the threads to finish */
    pthread_join(tid1[0], NULL);
    pthread_join(tid2[0], NULL);

    // terminates threads
    pthread_exit(NULL);

    // destroys semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    printf("\n");

    return 0;
}

// gcc name_of_program.c -lpthread -lrt