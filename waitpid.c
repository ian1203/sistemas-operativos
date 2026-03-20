#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pidA, pidB, pidM;
    int status;

    // Crear hijo A
    pidA = fork();
    if (pidA < 0) {
        perror("Error al crear A");
        exit(1);
    }
    if (pidA == 0) {
        sleep(10);
        printf("Hijo A -> PID: %d\n", getpid());
        exit(10);
    }

    // Crear hijo B
    pidB = fork();
    if (pidB < 0) {
        perror("Error al crear B");
        exit(1);
    }
    if (pidB == 0) {
        printf("Hijo B -> PID: %d\n", getpid());
        exit(0);
    }

    // Crear hijo M
    pidM = fork();
    if (pidM < 0) {
        perror("Error al crear M");
        exit(1);
    }
    if (pidM == 0) {
        sleep(3);
        printf("Hijo M -> PID: %d\n", getpid());
        exit(3);
    }

    // Padre Q espera en el orden: M, A, B

    waitpid(pidM, &status, 0);
    if (WIFEXITED(status)) {
        printf("Padre Q -> Hijo M terminó con retorno: %d\n", WEXITSTATUS(status));
    }

    waitpid(pidA, &status, 0);
    if (WIFEXITED(status)) {
        printf("Padre Q -> Hijo A terminó con retorno: %d\n", WEXITSTATUS(status));
    }

    waitpid(pidB, &status, 0);
    if (WIFEXITED(status)) {
        printf("Padre Q -> Hijo B terminó con retorno: %d\n", WEXITSTATUS(status));
    }

    return 0;
}