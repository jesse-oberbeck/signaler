#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

unsigned int num = 3;
int reverse_flag = 0;
int skip_flag = 0;
int exit_flag = 0;


unsigned int handle_args(int argc, char * argv[], unsigned int end)
{
    if (argc < 2){
        return(2);
    }
    for(int i = 0; i < argc; ++i){

        char * cur = argv[i];

        if (strncmp(cur, "-r", 2) == 0){
            reverse_flag = 1;
        }

        if (strncmp(cur, "-s", 2) == 0){
            unsigned int start = strtol(argv[i + 1], NULL, 10);
            if (start >= 0){
                num = start;
            }
        }

        if (strncmp(cur, "-e", 2) == 0){
            end = strtol(argv[i + 1], NULL, 10);
            if (end >= 0){
                exit_flag = 1;
            }
        }
    }
    return(end);
}

void handler (int sig_num)
{
    if (sig_num == SIGHUP){
        num = 3;
        reverse_flag = 0;
    }

    if (sig_num == SIGUSR1){
        skip_flag = 1;
    }
    if (sig_num == SIGUSR2){
        if (reverse_flag == 0){
            reverse_flag = 1;
        }
        else{
            reverse_flag = 0;
        }
    }
}

int main(int argc, char * argv[])
{

    unsigned int count = 2;
    unsigned int c = 2;
    int pid = getpid();
    unsigned int exit_num = 2;

    exit_num = handle_args(argc, argv, exit_num);

    for (;;)
    {

        signal(SIGHUP, handler);
        signal(SIGUSR1, handler);
        signal(SIGUSR2, handler);

        for (c = 2 ;c <= num - 1; c++)
        {
            if (num % c == 0)
            {
                break;
            }
        }
        if (c == num)
        {
            if (! skip_flag){
                printf("PID: %d\n", pid);
                printf("%d\n", num);
                sleep(1);
                count++;
            }else{
                skip_flag = 0;
            }
        }
////////////////////////////////////////////////////
        if (reverse_flag == 1){
            if (num <= exit_num){
                exit(0);
            }
            num--;
        }
        else{
            if ((num > exit_num) && (exit_flag == 1) || num >= UINT_MAX - 266){
                //UINT_MAX - 266 is the last prime possible in the data type.
                exit(0);
            }
            num++;
        }
    }
}
