/**
 * Name: Tiffany Nguyen
 * GPEL Username: gpel13.cs.nor.ou.edu -l nguy0850 (?)
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t p = fork();
    pid_t q = fork();

    // checking if fork worked
    if (p < 0)
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    // for the child process
    else if (p == 0)
    {
    }
    // for the other child process
    else if (q == 0)
    {
    }
    // for the parent process
    else
    {
        wait(NULL);
        printf("Child process complete.\n");
    }

    printf("This is the pid of the process: %d\n", p);
    printf("Hello world!, pid = %d \n", getpid());

    return 0;
}
