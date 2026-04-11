#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void manejador_sigint(int sig) {
    (void)sig;
    printf("\nEl usuario presionó CTRL+C\n");
    fflush(stdout);
    sleep(3);
    exit(0);
}

int main() {
    signal(SIGINT, manejador_sigint);

    while (1) {
        printf("ID del proceso R: %d\n", getpid());
        fflush(stdout);
        sleep(1);
    }

    return 0;
}