#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include <limits.h>
#include "signalerlib.h"

//Global because they need to be accessed by signal.
extern unsigned int num;
extern int reverse_flag;
extern int skip_flag;
extern int exit_flag;



int main(int argc, char * argv[])
{
    unsigned int count = 2;
    unsigned int c = 2;
    int pid = getpid();
    unsigned int exit_num = 2;

    exit_num = handle_args(argc, argv, exit_num);

    for (;;) {
        signal(SIGHUP, handler);
        signal(SIGUSR1, handler);
        signal(SIGUSR2, handler);

        //Prime generator.
        for (c = 2 ;c <= num - 1; c++) {
            if (num % c == 0) {
                break;
            }
        }
        if (c == num) {
            if (! skip_flag) {
                printf("PID: %d\n", pid);
                printf("%d\n", num);
                sleep(1);
                count++;
            } else {
                skip_flag = 0;
            }
        }

        //Exit on designated number whether incrementing or decrementing.
        if (reverse_flag == 1) {
            if (num <= exit_num) {
                exit(0);
            }
            num--;
        } else {
            if ((num > exit_num && exit_flag == 1) || (num >= UINT_MAX - 266)){
                //UINT_MAX - 266 is the last prime possible in the data type.
                exit(0);
            }
            num++;
        }
    }
}
