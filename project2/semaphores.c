/**
 * Name: Tiffany Nguyen
 * VM: cs093.cs.ourcloud.ou.edu
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SEMKEY ((key_t)400L) // semaphore key
#define NSEMS 1              // number of semaphores being created
#define SHMKEY ((key_t)1497) // shared memory key

/* semaphore id */
int sem_id;

/* semaphore buffer */
static struct sembuf OP = {0, -1, 0};
static struct sembuf OV = {0, 1, 0};
struct sembuf *P = &OP;
struct sembuf *V = &OV;

/* semapore union used to generate semaphore */
typedef union
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
} semunion;

semunion semctl_arg;

/* shared memory */
typedef struct
{
    int value;
} shared_mem;

int process1(shared_mem *total);
int process2(shared_mem *total);
int process3(shared_mem *total);
int process4(shared_mem *total);
int POP();
int VOP();

/* POP (wait()) function for semaphore to protect critical section */
int POP()
{
    int status;
    status = semop(sem_id, P, 1);
    return status;
}

/* VOP (signal()) function for semaphore to release protection */
int VOP()
{
    int status;
    status = semop(sem_id, V, 1);
    return status;
}

/* methods for processes; each process increments the shared memory value */
int process1(shared_mem *total)
{
    for (int i = 0; i < 100000; ++i)
    {
        POP();
        // in the critical section
        total->value += 1;
        VOP();
    }
    printf("From process 1: counter = %d\n", total->value);
    return 0;
}

int process2(shared_mem *total)
{
    for (int i = 0; i < 200000; ++i)
    {
        POP();
        // in the critical section
        total->value += 1;
        VOP();
    }
    printf("From process 2: counter = %d\n", total->value);
    return 0;
}

int process3(shared_mem *total)
{
    for (int i = 0; i < 300000; ++i)
    {

        POP();
        // in the critical section
        total->value += 1;
        VOP();
    }
    printf("From process 3: counter = %d\n", total->value);
    return 0;
}

int process4(shared_mem *total)
{
    for (int i = 0; i < 500000; ++i)
    {
        POP();
        // in the critical section
        total->value += 1;
        VOP();
    }
    printf("From process 4: counter = %d\n", total->value);
    return 0;
}

int main()
{
    int value, value1;
    semctl_arg.val = 1;

    int shmid, pid1, pid2, pid3, pid4, ID, status;
    char *shmadd;
    shmadd = (char *)0;

    /* pointer for shared memory */
    shared_mem *total;

    /* create and connect to a shared memory segment and allocates shared memory */
    if ((shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    /* attaches to shared memory and initializes shared memory */
    if ((total = (shared_mem *)shmat(shmid, shmadd, 0)) == (shared_mem *)-1)
    {
        perror("shmat");
        exit(0);
    }

    /* Create semaphores */
    sem_id = semget(SEMKEY, NSEMS, IPC_CREAT | 0666);
    if (sem_id < 0)
    {
        perror("Error in creating the semaphore.\n");
        exit(1);
    }

    /* Initialize semaphore */
    value1 = semctl(sem_id, 0, SETVAL, semctl_arg);
    if (value1 < 0)
    {
        perror("Error detected in SETVAL.\n");
        exit(1);
    }
    value = semctl(sem_id, 0, GETVAL, semctl_arg);
    if (value < 0)
    {
        perror("Error detected in GETVAL.\n");
        exit(1);
    }

    /* forks for the four child processes */
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

    /* parent process waiting for each child to finish */
    for (int i = 0; i < 4; ++i)
    {
        int pid = wait(NULL);
        printf("Child with ID %d has just exited.\n", pid);
    }

    /* detatch shared memory */
    if (shmdt(total) == -1)
    {
        perror("shmdt");
        exit(-1);
    }

    /* remove shared memory */
    if (shmctl(shmid, IPC_RMID, (struct shmid_ds *)0) == -1)
    {
        perror("shmctl");
        exit(-1);
    }

    /* De-allocate semaphore */
    semctl_arg.val = 0;
    status = semctl(sem_id, 0, IPC_RMID, semctl_arg);
    if (status < 0)
    {
        printf("Error in removing the semaphore.\n");
    }

    printf("End of Program\n");
    return 0;
}
