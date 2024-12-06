#include <signal.h>
#include <setjmp.h>
#include <stdio.h>

volatile sig_atomic_t sig_flag;
jmp_buf catch_pos;

void handle_fpe(int sig_num) {
    sig_flag = 1;
    longjmp(catch_pos, 1);
}

int main(int argc, char* argv[]) {
    int x, fail_val;

    signal(SIGFPE, handle_fpe);
    sig_flag = 0;

    if ((fail_val = setjmp(catch_pos)) == 0) {
        x = 42 / 0;
    }
    printf("%i\n", fail_val);

    if (sig_flag) {
        printf("beyond good and evil\n");
    }

    return 0;
}