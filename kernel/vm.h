#ifndef VM_H
#define VM_H

int mprotect(void *addr, int len);
int munprotect(void *addr, int len);

#endif // VM_H
