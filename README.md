# Implementación de Permisos Básicos en xv6

## Funcionamiento y Lógica

El objetivo principal de esta modificación es implementar un sistema de permisos básicos en xv6 para controlar las operaciones de lectura y escritura sobre los archivos, además de agregar un permiso especial de inmutabilidad. Este sistema asegura que:

1. **Control de Acceso:**
   - Cada archivo tiene un conjunto de permisos asociados definidos en el `inode`. Estos permisos determinan si se permite su lectura, escritura o ambas.
   - Las operaciones de apertura, lectura y escritura respetan estos permisos y devuelven errores cuando se intenta realizar una operación no permitida.

2. **Permiso Especial:**
   - Se introduce un permiso especial (`5`) que marca el archivo como "inmutable". Un archivo inmutable es considerado como solo lectura y no permite que sus permisos sean modificados.

3. **Nueva Llamada al Sistema `chmod`:**
   - La llamada al sistema `chmod` permite a los usuarios cambiar los permisos de un archivo, salvo cuando este ha sido marcado como inmutable.

4. **Validación de Permisos:**
   - Las funciones asociadas con las operaciones de archivos han sido modificadas para verificar los permisos antes de realizar cualquier operación.

---

## Explicación de las Modificaciones Realizadas

### Archivos Modificados

1. **`kernel/fs.h`:**
   - Se agregó un nuevo campo `permissions` en la estructura `inode` para almacenar los permisos del archivo. Este campo es un entero donde:
     - `0`: Sin permisos.
     - `1`: Solo lectura.
     - `2`: Solo escritura.
     - `3`: Lectura y escritura (valor predeterminado al crear un archivo).
     - `5`: Inmutable (solo lectura, no se puede modificar el permiso).

2. **`kernel/fs.c`:**
   - En la función `ialloc`, se inicializó el campo `permissions` de los `inode` con el valor `3` (lectura y escritura).

3. **`kernel/sysfile.c`:**
   - **`sys_open`:** 
     - Verifica los permisos del archivo antes de abrirlo. Si los permisos no coinciden con el modo solicitado (`omode`), la operación falla.
   - **`sys_write` y `sys_read`:**
     - Verifican los permisos del archivo antes de realizar operaciones de lectura o escritura.
   - **Nueva función `chmod`:**
     - Implementa la lógica para cambiar los permisos de un archivo, verificando que no esté marcado como inmutable.

4. **`kernel/syscall.c` y `kernel/syscall.h`:**
   - Se registró la nueva llamada al sistema `chmod`.
   - Se asignó un número único a `chmod` en la tabla de llamadas al sistema.

5. **`user/user.h`:**
   - Se agregó la declaración de la nueva llamada al sistema `chmod`.

6. **`user/ulib.c` y `user/usys.pl`:**
   - Se incluyó la implementación y el soporte para la nueva llamada al sistema.

7. **`mkfs/mkfs.c`:**
   - Se actualizaron las estructuras del sistema de archivos para incluir el nuevo campo `permissions`.

8. **Pruebas:**
   - Se creó un programa de prueba en `user/test_chmod.c` que:
     - Crea un archivo.
     - Cambia sus permisos con `chmod`.
     - Verifica que las operaciones respeten los permisos definidos.
     - Prueba la funcionalidad del permiso de inmutabilidad.

### Impacto en Otras Áreas del Sistema

- **`kernel/console.c`, `kernel/vm.c`, y otros:** Estos archivos fueron modificados indirectamente como parte del impacto de las nuevas verificaciones de permisos y para garantizar que no se introdujeran errores en otras áreas del kernel.
- **`kernel/proc.c` y `kernel/sysproc.c`:** Estos archivos fueron revisados para asegurar que las funciones relacionadas con procesos no interfieran con los permisos de los archivos.

---

## Pruebas Realizadas

1. **Pruebas Básicas:**
   - Crear un archivo y escribir en él con permisos de lectura/escritura.
   - Cambiar los permisos a solo lectura y verificar que la escritura falle.
   - Restaurar los permisos a lectura/escritura y verificar que las operaciones se permitan.

2. **Pruebas de Inmutabilidad:**
   - Marcar un archivo como inmutable y verificar que no permita escritura.
   - Intentar cambiar los permisos de un archivo inmutable y confirmar que falle.

---

## Dificultades Encontradas

1. **Modificaciones en el sistema de archivos:**
   - Se presentaron dificultades al agregar el nuevo campo `permissions` en la estructura `inode`, ya que afectó múltiples áreas del sistema, incluyendo `mkfs` y la inicialización de discos.

2. **Verificación de Permisos:**
   - La integración de las verificaciones de permisos en `sys_open`, `sys_write`, y `sys_read` fue compleja debido a la necesidad de garantizar que no se introdujeran errores en operaciones existentes.

3. **Permiso de Inmutabilidad:**
   - La lógica para bloquear cambios de permisos en archivos inmutables requirió cambios específicos en la llamada al sistema `chmod` para devolver errores apropiados.

---

