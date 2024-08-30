#include "user.h"

int main(void) {
    int ppid = getppid();
    printf("El PID del proceso padre es: %d\n", ppid);
    exit(0);
}
