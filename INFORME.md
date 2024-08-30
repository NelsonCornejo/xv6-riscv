## Funcionamiento de las llamadas al sistema

Las llamadas al sistema implementadas son `getppid()` y `getancestor(int)`. 

- **`getppid()`**: Esta llamada devuelve el PID del proceso padre del proceso actual. Es útil para conocer la jerarquía de procesos y rastrear el origen de un proceso en particular.
  
- **`getancestor(int n)`**: Esta llamada devuelve el PID del ancestro `n` niveles por encima del proceso actual. Por ejemplo, `getancestor(1)` devuelve el PID del padre, `getancestor(2)` devuelve el PID del abuelo, y así sucesivamente. Si el número proporcionado es mayor que el número de ancestros disponibles, se devuelve `-1`.

## Explicación de las modificaciones realizadas


1. **Definición de las llamadas al sistema**: 
   Se agregaron las funciones `sys_getppid()` y `sys_getancestor()` en `sysproc.c` para manejar la lógica de estas nuevas llamadas. 

2. **Modificación de `syscall.c` y `syscall.h`**: 
   Se agregaron los prototipos de las funciones y se actualizaron las tablas de llamadas al sistema para incluir `SYS_getppid` y `SYS_getancestor`.

3. **Creación de programas de prueba**:
   Se crearon los programas `yosoytupadre.c` y `yosoyantecesor.c` para verificar el correcto funcionamiento de las llamadas al sistema. Estos programas se compilaron y ejecutaron como parte del entorno xv6.

## Dificultades encontradas y cómo se resolvieron

1. **Problema con la implementación de `getancestor(int)`**:
   Al principio, hubo problemas para manejar correctamente los argumentos pasados a la llamada al sistema. Esto se resolvió asegurando que la función `argint()` se implementara correctamente para recuperar el parámetro `n` y se realizó un manejo adecuado de errores para casos donde `n` era negativo o superaba el número de ancestros disponibles.

2. **Errores de compilación en `syscall.c`**:
   Durante la implementación, surgieron conflictos de tipos en la función `argint`. Esto se debió a errores de referencia en la estructura `trapframe`. Se resolvió al asegurarnos de que los nombres de los miembros de la estructura fueran correctos y consistentes en todo el código.

3. **Problemas al ejecutar `make qemu`**:
   En algunos momentos, el sistema no arrancaba correctamente después de agregar nuevas llamadas al sistema. Esto fue solucionado revisando y corrigiendo las modificaciones en `Makefile`, asegurándonos de que todos los archivos fuente y dependencias estuvieran correctamente configurados.
