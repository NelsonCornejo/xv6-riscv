#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int main() {
    // Obtener la dirección actual del heap
    char *addr = sbrk(0);  // Dirección actual del heap
    
    // Reservar una página
    sbrk(4096);  // 4096 bytes = 1 página

    // Intentar proteger la nueva página
    if (mprotect(addr, 1) < 0) {  // Cambiado a 1 para indicar una página
        printf("mprotect falló\n");
        exit(1);
    }

    // Intentar escribir en la página protegida
    printf("Intentando escribir en la página protegida...\n");
    addr[0] = 'A';  // Esto debería fallar si la protección funciona

    // Verifica si la escritura falló
    printf("Escritura en página protegida: %c\n", addr[0]);
    printf("sfence_vma1 ejecutado, cambios aplicados.\n");

    // Elimina la protección de solo lectura usando munprotect (1 página)
    if (munprotect(addr, 1) < 0) {  // Cambiado a 1 para indicar una página
        printf("munprotect falló\n");
        exit(1);
    }

    // Intentar escribir en la página nuevamente
    printf("Intentando escribir en la página después de munprotect...\n");
    addr[0] = 'B';  // Esto debería ser exitoso después de munprotect

    // Verifica si la escritura fue exitosa
    printf("Escritura en página después de munprotect: %c\n", addr[0]);

    exit(0);
    printf("sfence_vma2 ejecutado, cambios aplicados.\n");
}
