/**
 * Name: Tiffany Nguyen
 * GPEL Username: gpel13@cs.nor.ou.edu -l nguy0850
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define SHMKEY ((key_t)1497) // global SHMKEY yipee

// shared memory
typedef struct
{
    int value;
} shared_mem;

int process1(shared_mem *total);
int process2(shared_mem *total);
int process3(shared_mem *total);
int process4(shared_mem *total);

int main()
{
    int shmid, pid1, pid2, pid3, pid4, ID, status; // initializing the stuffs
    char *shmadd;
    shmadd = (char *)0;

    shared_mem *total; // pointer for shared memory !!

    // create and connect to a shared memory segment
    // allocates shared memory
    if ((shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    // attaches to shared memory
    if ((total = (shared_mem *)shmat(shmid, shmadd, 0)) == (shared_mem *)-1)
    {
        perror("shmat");
        exit(0);
    }

    // initialize shared memory
    total->value = 0;

    // fork for the 4 child processes
    if ((pid1 = fork()) == 0)
    {
        process1(total);
        exit(0);
    }

    if ((pid2 = fork()) == 0)
    {
        process2(total);
        exit(0);
    }

    if ((pid3 = fork()) == 0)
    {
        process3(total);
        exit(0);
    }

    if ((pid4 = fork()) == 0)
    {
        process4(total);
        exit(0);
    }

    // parent process waiting for each child to finish
    for (int i = 0; i < 4; ++i)
    {
        int pid = wait(NULL);
        printf("Child with ID %d has just exited.\n", pid);
    }

    // detatch shared memory
    if (shmdt(total) == -1)
    {
        perror("shmdt");
        exit(-1);
    }

    // remove shared memory
    if (shmctl(shmid, IPC_RMID, (struct shmid_ds *)0) == -1)
    {
        perror("shmctl");
        exit(-1);
    }

    printf("End of Program\n");
    return 0;
}

// methods for processes; each process increments the shared memory value while the value is under a specific limit
int process1(shared_mem *total)
{
    for (int i = 0; i < 100000; ++i)
    {
        total->value += 1;
    }
    printf("From process 1: counter = %d\n", total->value);
    return 0;
}

int process2(shared_mem *total)
{
    for (int i = 0; i < 200000; ++i)
    {
        total->value += 1;
    }
    printf("From process 2: counter = %d\n", total->value);
    return 0;
}

int process3(shared_mem *total)
{
    for (int i = 0; i < 300000; ++i)
    {
        total->value += 1;
    }
    printf("From process 3: counter = %d\n", total->value);
    return 0;
}

int process4(shared_mem *total)
{
    for (int i = 0; i < 500000; ++i)
    {
        total->value += 1;
    }
    printf("From process 4: counter = %d\n", total->value);
    return 0;
}
