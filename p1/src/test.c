#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/times.h>
size_t const count = 5;
size_t pids_children[count];

void kill_children(int signum)
{
    for (size_t i = 0; i < count; i++)
    {
        kill(pids_children[i], SIGTERM); //wait for the 5 children and gather time
    }
}

int main()
{

    pid_t ppid = fork();
    if (ppid == 0)
    { //first child

        for (size_t i = 0; i < count; i++) //fork 5 children(or 5 grandchildren) from  the first child and set them in an endless loop
        {
            pid_t pid = fork();
            if (pid == 0)
            {

                while (1)
                {
                }
            }

            else if (pid < 0)
            {
                perror("error forking from child ");
            }
            else
            {
                pids_children[i] = pid;
            }
        }

        if (signal(SIGUSR1, kill_children) == SIG_ERR) //set signal to the first child  so it print the time gathered by wait()
        {
            perror("cannot create signal");
            exit(1);
        }

        for (size_t i = 0; i < count; i++)
        {
            waitpid(pids_children[i], NULL, 0); //wait for the 5 children and gather time
        }
        struct tms t;
        perror("about to print time");
        if ((times(&t)) == -1)
        {
            perror("error times");
            exit(1);
        }

        else
        {
            int tics_per_second = sysconf(_SC_CLK_TCK);
             printf("            utime           stime\n");
    printf("parent:    %f        %f\n",
           ((double) t.tms_utime)/tics_per_second,
           ((double) t.tms_stime)/tics_per_second);
    printf("child:     %f        %f\n",
           ((double) t.tms_cutime)/tics_per_second,
           ((double) t.tms_cstime)/tics_per_second);
            exit(0);
        }
    }

    else if (ppid > 0)
    { //parent

        sleep(5);
        perror("going good");

        kill(ppid, SIGUSR1); 
        waitpid(ppid,NULL,0);
    }
    else
    {

        perror("error");
        exit(1);
    }

    return 0;
}