#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

volatile sig_atomic_t sigusr1_recibida = 0;
volatile sig_atomic_t sigusr2_recibida = 0;
volatile sig_atomic_t alarma_recibida = 0;

void manejador_sigusr1(int sig) {
    (void)sig;
    printf("Recibí la señal SIGUSR1. Mi ID es %d y el ID de mi padre es %d\n",
           getpid(), getppid());
    fflush(stdout);
    sigusr1_recibida = 1;
}

void manejador_sigusr2(int sig) {
    (void)sig;
    printf("Recibí la señal SIGUSR2. Mi ID es %d y el ID de mi padre es %d\n",
           getpid(), getppid());
    fflush(stdout);
    sigusr2_recibida = 1;
}

void manejador_alarma(int sig) {
    (void)sig;
    printf("Alarma recibida\n");
    fflush(stdout);
    alarma_recibida = 1;
}

int main() {
    pid_t pidA, pidC;

    pidA = fork();

    if (pidA < 0) {
        perror("Error en fork para A");
        exit(1);
    }

    if (pidA == 0) {
        signal(SIGUSR1, manejador_sigusr1);

        pidC = fork();

        if (pidC < 0) {
            perror("Error en fork para C");
            exit(1);
        }

        if (pidC == 0) {
            signal(SIGUSR2, manejador_sigusr2);

            while (!sigusr2_recibida) {
                pause();
            }

            exit(0);
        } else {
            while (!sigusr1_recibida) {
                pause();
            }

            kill(pidC, SIGUSR2);
            waitpid(pidC, NULL, 0);
            exit(0);
        }
    } else {
        signal(SIGALRM, manejador_alarma);
        alarm(3);

        while (!alarma_recibida) {
            pause();
        }

        kill(pidA, SIGUSR1);
        waitpid(pidA, NULL, 0);

        printf("Mis hijos han terminado.\n");
        fflush(stdout);
    }

    return 0;
}