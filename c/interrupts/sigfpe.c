#include <signal.h>
#include <setjmp.h>
#include <stdio.h>

void handler(int signal_number);
void fpe_handler(int signal_number);

volatile sig_atomic_t sig_flag;
jmp_buf catch_position;

int main(int argc, char* argv[]) {
    struct sigaction old, new;
    new.sa_handler = handler;
    
    sigaction(SIGSEGV, &new, &old);
    
    // TRIGGER SEGMENTATION FAULT
    //int* a = 42;
//    int b = *a;

    // FLOATING POINT ERROR
    int fail_value;

    signal(SIGFPE, fpe_handler);
    sig_flag = 0;

    if ((fail_value = setjmp(catch_position)) == 0) {
        int x = 42 / 0;
    }

    if (sig_flag) printf("Beyond good and evil\n");
  
    return 0;
}

void handler(int signal_number) {
    printf("Segmentation fault handler\n");
}

void fpe_handler(int signal_number) {
    sig_flag = 1;

    longjmp(catch_position, 1);
}
