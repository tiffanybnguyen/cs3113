/**
 * Name: Tiffany Nguyen
 * GPEL Username: gpel13.cs.nor.ou.edu -l nguy0850 (?)
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define SHMKEY ((key_t)1497) // Define global SHMKEY

int process1();
int process2();
int process3();
int process4();

int main()
{
    int shmid, pid1, pid2, pid3, pid4, ID, status;
    char *shmadd;
    shmadd = (char *)0;

    // shared memory
    typedef struct
    {
        int value;
    } shared_mem;

    shared_mem *total;

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

    // add stuff here
    // create processes
    // if ((pid1 = fork()) == 0)
    // {
    //     process1();
    // }

    for (int i = 0; i < 4; ++i)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        pid_t pid = wait(NULL);
        printf("Process %d is terminated.\n", pid);
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

    return 0;

    /*
    //parent wait for child processes to finish and print ID of each child in three ways
        wait(&status);
        wait (NULL);
        waitpid(pid1, NULL, 0);
        printf("Child with pid %d has just exited .\n", pid1);
    */

    /*
    Notes:
     - process1 increases the value of shared variable "total" * by some number

     - if you did not remove your shared memory segmetnts (e.g. program crashes before the execution of shmctl()), they will be in the
       system forever. This will degrade the system performance.
     - use the ipcs command to check if you have shared memory segments left in the system
     - use the ipcrm command to removed your shared memory segments

    Procedure for Using Shared Memory
     - find a key: Unix uses this key for idenitfying shared memory segments
     - use shmget() to allocate shared memory
     - use shmat() to attach a shared memory to an address space
     - use shmdt() to detatch a shared memory from an address space
     - use scmctl() to deallocate a shared memory

    */
}

int process1()
{
    exit(0);
    return 0;
}

int process2()
{
    exit(0);
    return 0;
}

int process3()
{
    exit(0);
    return 0;
}

int process4()
{
    exit(0);
    return 0;
}
