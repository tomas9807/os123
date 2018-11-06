#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/times.h>
size_t current_count;
size_t *pids_children;

void kill_children(int signum)
{
    for (size_t i = 0; i < current_count; i++)
    {
        kill(pids_children[i], SIGTERM); //wait for the 5 children and gather time
    }
}

int main(int argc, char *argv[])
{
    if (argc == 6)
    {

        int tics_per_second = sysconf(_SC_CLK_TCK);
        __uid_t uid1;
        size_t count1;
        __uid_t uid2;
        size_t count2;

        uid1 = (__uid_t)atoi(argv[1]);
        count1 = (size_t)atoi(argv[2]);
        uid2 = (__uid_t)atoi(argv[3]);
        count2 = (size_t)atoi(argv[4]);
        size_t time_ = (size_t)atoi(argv[5]);

        pid_t ppid_udi1 = fork();
        if (ppid_udi1 == 0)
        {
            if (setuid(uid1) < 0)
            {
                perror("error el uid1 no existe o es del root y el programa se ejecuto sin privilegios de root");
                exit(1);
            }
            pids_children = malloc(sizeof(int) * count1);
            current_count = count1;
            for (size_t i = 0; i < count1; i++) //fork 5 children(or 5 grandchildren) from  the first child and set them in an endless loop
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

            for (size_t i = 0; i < count1; i++)
            {
                waitpid(pids_children[i], NULL, 0); //wait for the 5 children and gather time
            }
            struct tms t;

            if ((times(&t)) == -1)
            {
                perror("error times");
                exit(1);
            }

            else
            {
                double usertime = (double)t.tms_cutime / tics_per_second;
                double systime = (double)t.tms_cstime / tics_per_second;
                double sumtime = usertime + systime;
                printf("  %u   %zu    %f    %f    %f \n", uid1, count1, usertime, systime, sumtime);
                exit(0);
            }
        }

        else if (ppid_udi1 > 0)
        { //parent

            pid_t ppid_udi2 = fork();
            if (ppid_udi2 == 0)
            {
                if (setuid(uid2) < 0)
                {
                    perror("error el uid2 no existe o es del root y el programa se ejecuto sin privilegios de root");
                    exit(1);
                }
                pids_children = malloc(sizeof(int) * count2);
                current_count = count2;
                for (size_t i = 0; i < count2; i++) //fork 5 children(or 5 grandchildren) from  the first child and set them in an endless loop
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

                for (size_t i = 0; i < count2; i++)
                {
                    waitpid(pids_children[i], NULL, 0); //wait for the 5 children and gather time
                }
                struct tms t;

                if ((times(&t)) == -1)
                {
                    perror("error times");
                    exit(1);
                }

                else
                {

                    double usertime = (double)t.tms_cutime / tics_per_second;
                    double systime = (double)t.tms_cstime / tics_per_second;
                    double sumtime = usertime + systime;
                    printf("  %u   %zu    %f    %f    %f \n", uid2, count2, usertime, systime, sumtime);

                    exit(0);
                }
            }
            else if (ppid_udi2 < 0)
            {
                perror("error forking uid2");
                exit(1);
            }
            puts("  UID  COUNT  USERTIME   SYSTEMTIME   USER+SYSTEM \n");
            sleep(time_);

            kill(ppid_udi1, SIGUSR1);
            kill(ppid_udi2, SIGUSR1);
            waitpid(ppid_udi1, NULL, 0);
            waitpid(ppid_udi2, NULL, 0);
        }
        else
        {

            perror("error forking child uid1");
            exit(1);
        }

        return 0;
    }
    else
    {
        perror("no hay suficientes parametros la sintaxis es: ts uid1 count1 uid2 count2 time");
        exit(1);
    }
}