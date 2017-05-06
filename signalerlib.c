#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include "signalerlib.h"

extern unsigned int num = 3;
extern int reverse_flag = 0;
extern int skip_flag = 0;
extern int exit_flag = 0;

unsigned int handle_args(int argc, char * argv[], unsigned int end)
{
    //Processes arguments passed on the command line.

    if (argc < 2) {
        return(2);
    }
    for(int i = 0; i < argc; ++i) {

        char * cur = argv[i];

        if (strncmp(cur, "-r", 2) == 0) {
            reverse_flag = 1;
        }

        if (strncmp(cur, "-s", 2) == 0){
            unsigned int start = strtol(argv[i + 1], NULL, 10);
            num = start;
        }

        if (strncmp(cur, "-e", 2) == 0) {
            end = strtol(argv[i + 1], NULL, 10);
            exit_flag = 1;
        }
    }
    return(end);
}

void handler (int sig_num)
{

    //Catch and react to signals.

    if (sig_num == SIGHUP) {
        num = 3;
        reverse_flag = 0;
    }

    if (sig_num == SIGUSR1) {
        skip_flag = 1;
    }
    if (sig_num == SIGUSR2) {
        if (reverse_flag == 0) {
            reverse_flag = 1;
        } else {
            reverse_flag = 0;
        }
    }
}
