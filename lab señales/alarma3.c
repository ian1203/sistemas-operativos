#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t pidB = -1;

void manejador_sigalrm(int sig) {
    (void)sig;
    printf("Alarma recibida\n");
    fflush(stdout);
    exit(1);
}

int main() {
    pid_t pidC;

    pidB = fork();

    if (pidB < 0) {
        perror("Error en fork para B");
        exit(1);
    }

    if (pidB == 0) {
        signal(SIGALRM, manejador_sigalrm);

        pidC = fork();

        if (pidC < 0) {
            perror("Error en fork para C");
            exit(1);
        }

        if (pidC == 0) {
            while (1) {
                printf("Esperando una señal.\n");
                fflush(stdout);
                sleep(1);
            }
        } else {
            sleep(1);
            kill(pidC, SIGKILL);
            while (1) {
                pause(); 
            }
        }
    } else {
        sleep(5);
        kill(pidB, SIGALRM);
        waitpid(pidB, NULL, 0);
    }

    return 0;
}