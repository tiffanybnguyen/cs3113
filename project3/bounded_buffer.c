#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>

pthread_t tid1[1];      /* process id for thread 1 */
pthread_t tid2[1];      /* process id for thread 2 */
pthread_attr_t attr[1]; /* attribute pointer array */

sem_t sem1;

// void sem_wait(&sem1);
// void sem_post(&sem1);
// void sem_init(&sem1, ..., ...);
// void sem_destroy(&sem1);

int main()
{
    printf("Hello world! \n");

    fflush(stdout);
    /* Required to schedule thread independently.*/
    pthread_attr_init(&attr[0]);
    pthread_attr_setscope(&attr[0], PTHREAD_SCOPE_SYSTEM);
    /* end to schedule thread independently */

    /* Create the threads */
    pthread_create(&tid1[0], &attr[0], thread1, NULL);
    pthread_create(&tid2[0], &attr[0], thread2, NULL);

    /* Wait for the threads to finish */
    pthread_join(tid1[0], NULL);
    pthread_join(tid2[0], NULL);
    // ....................................................Terminate threads
    pthread_exit(NULL);

    /* Below is a piece of “C” code that gives you some idea of how to open file and read from file
    char newChar;
    FILE *fp;
    fp = fopen("mytest.dat", "r");
    while (fscanf(fp, "%c", &newChar) != EOF) */

    return 0;
}

// gcc name_of_program.c -lpthread -lrt