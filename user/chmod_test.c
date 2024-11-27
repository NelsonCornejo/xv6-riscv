#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    char *filename = "testfile";

    // Crear archivo
    int fd = open(filename, O_CREATE | O_RDWR);
    write(fd, "Hola Mundo\n", 11);
    close(fd);

    // Cambiar a solo lectura
    if (chmod(filename, 1) < 0) {
        printf("Error al cambiar a solo lectura\n");
        exit(1);
    }
    if (open(filename, O_WRONLY) == -1) {
        printf("Correctamente bloqueado para escritura\n");
    } else {
        printf("Error: Se permitió escritura en archivo de solo lectura\n");
    }

    // Cambiar de vuelta a lectura/escritura
    if (chmod(filename, 3) < 0) {
        printf("Error al cambiar a lectura/escritura\n");
        exit(1);
    }
    fd = open(filename, O_WRONLY);
    write(fd, "Editado\n", 8);
    close(fd);

    printf("Pruebas completadas correctamente\n");
    exit(0);
}
