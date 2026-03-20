#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int numero_aleatorio() {
    return rand() % 100;  // número entre 0 y 99
}

void proceso_hijo(const char *nombre) {
    srand(getpid());  // semilla distinta por proceso
    printf("Hijo %s -> PID: %d, número aleatorio: %d\n", nombre, getpid(), numero_aleatorio());
    exit(0);  // termina correctamente
}

int main() {
    pid_t pidA, pidB, pidM;
    int status;
    int hijos_correctos = 0;

    pidA = fork();
    if (pidA < 0) {
        perror("Error al crear A");
        exit(1);
    }
    if (pidA == 0) {
        proceso_hijo("A");
    }

    pidB = fork();
    if (pidB < 0) {
        perror("Error al crear B");
        exit(1);
    }
    if (pidB == 0) {
        proceso_hijo("B");
    }

    pidM = fork();
    if (pidM < 0) {
        perror("Error al crear M");
        exit(1);
    }
    if (pidM == 0) {
        proceso_hijo("M");
    }

    // Padre Q espera a todos los hijos
    for (int i = 0; i < 3; i++) {
        pid_t terminado = wait(&status);
        if (terminado > 0) {
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                hijos_correctos++;
            }
        }
    }

    printf("Padre Q -> Número de hijos que terminaron correctamente: %d\n", hijos_correctos);

    return 0;
}