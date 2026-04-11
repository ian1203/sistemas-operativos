#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void manejador_alarma(int sig) {
    (void)sig;
    printf("Transcurrieron 3 segundos\n");
    fflush(stdout);
}

int main() {
    signal(SIGALRM, manejador_alarma);

    alarm(3);

    while (1) {
        pause();  
    }

    return 0;
}