#include "kernel/types.h" 
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main() {
    char *filename = "testfile";

    // Crear archivo
    int fd = open(filename, O_CREATE | O_RDWR);
    write(fd, "Hola Mundo\n", 11);
    close(fd);

    // Verificar permisos iniciales
    struct stat st;
    if (stat(filename, &st) < 0) {
        printf("Error al obtener estado del archivo\n");
        exit(1);
    }
    printf("Permisos iniciales: %d\n", st.permissions);

    // Cambiar a solo lectura
    if (chmod(filename, 1) < 0) {
        printf("Error al cambiar a solo lectura\n");
        exit(1);
    }
    if (stat(filename, &st) == 0) {
        printf("Permisos después de chmod(1): %d\n", st.permissions);
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
    if (stat(filename, &st) == 0) {
        printf("Permisos después de chmod(3): %d\n", st.permissions);
    }

    fd = open(filename, O_WRONLY);
    write(fd, "Editado\n", 8);
    close(fd);

    // Leer el contenido del archivo
    char buf[20];
    fd = open(filename, O_RDONLY);
    read(fd, buf, sizeof(buf));
    close(fd);
    printf("Contenido del archivo: %s\n", buf);

    // Eliminar el archivo
    unlink(filename);
    printf("Pruebas completadas correctamente\n");
    exit(0);
}
