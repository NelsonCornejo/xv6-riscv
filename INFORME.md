# Informe de Instalación de xv6 con riscv

1. Cloné el repositorio de xv6 desde el PPT de la clase.
2. Verifiqué e instalé las herramientas necesarias (gcc, qemu, make, etc.).
3. Modifiqué el código para solucionar errores relacionados con `menvcfg` y `stimecmp`.
4. Compilé el proyecto usando `make`.
5. Ejecuté xv6 en QEMU para verificar su funcionamiento.

## Problemas Encontrados y Soluciones
- **Error al compilar relacionado con `menvcfg` y `stimecmp`**:
  - **Solución**: Comentar las líneas problemáticas en el archivo `riscv.h`,`stats.h` y `trap.h`.

## Confirmación de que xv6 está Funcionando Correctamente
- Se confirmó que xv6 arranca correctamente en QEMU, mostrando el mensaje de inicio del kernel y 
  permitiendo la ejecución de comandos básicos en la shell.
