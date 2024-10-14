#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

// Variable global de bloqueo para la salida estándar
volatile int print_lock = 0;

// Función para adquirir el lock
void acquire_lock() {
  while (__sync_lock_test_and_set(&print_lock, 1)) {
    // Espera activa hasta que el lock esté disponible
  }
}

// Función para liberar el lock
void release_lock() {
  __sync_lock_release(&print_lock);
}

int main(void) {
  int total_procesos = 20;  // Cambiar a un número más bajo para pruebas rápidas
  int pids[total_procesos]; // Arreglo para almacenar los PIDs de los hijos

  // Crear procesos para prueba
  for (int i = 0; i < total_procesos; i++) {
    int pid = fork();
    if (pid == 0) {  // Proceso hijo
      // Aquí el proceso hijo no imprime nada, solo termina
      exit(0);  // Terminar el proceso hijo correctamente
    } else if (pid > 0) {
      // Proceso padre guarda los PIDs de los hijos
      pids[i] = pid;
    } else {
      // Error al crear proceso
      acquire_lock();
      printf("Error al crear el proceso hijo %d\n", i);
      release_lock();
    }
  }

  // Proceso padre realiza toda la impresión
  for (int i = 0; i < total_procesos; i++) {
    acquire_lock();
    printf("Proceso padre creó hijo %d con PID: %d\n", i, pids[i]);
    release_lock();
  }

  // Esperar a que todos los procesos hijos terminen
  for (int i = 0; i < total_procesos; i++) {
    int status;
    int pid = wait(&status);  // Esperar a que el proceso hijo termine
    acquire_lock();
    printf("Proceso hijo con PID: %d terminó con estado: %d\n", pid, status);
    release_lock();
  }

  // Todos los procesos han terminado
  acquire_lock();
  printf("Todos los procesos hijos han terminado.\n");
  release_lock();

  exit(0);
}
