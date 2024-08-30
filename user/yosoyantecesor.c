#include "user.h"

int main(void) {
    int pid_actual = getpid();
    int pid_padre = getancestor(1);
    int pid_abuelo = getancestor(2);

    printf("PID actual: %d\n", pid_actual);
    printf("PID del padre: %d\n", pid_padre);
    printf("PID del abuelo: %d\n", pid_abuelo);

    // Probar un caso inválido, por ejemplo, un ancestro que no existe.
    int pid_invalido = getancestor(3);
    printf("PID inválido (esperado -1): %d\n", pid_invalido);

    exit(0);
}
