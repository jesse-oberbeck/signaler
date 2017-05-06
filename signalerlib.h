#ifndef SIGNALERLIB_H
#define SIGNALERLIB_H

extern unsigned int num;
extern int reverse_flag;
extern int skip_flag;
extern int exit_flag;

unsigned int handle_args(int argc, char * argv[], unsigned int end);

void handler (int sig_num);

#endif
