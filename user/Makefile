# Compilador y banderas
CC = riscv64-unknown-elf-gcc
CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb -gdwarf-2 -MD -mcmodel=medany \
         -fno-common -nostdlib -fno-builtin-strncpy -fno-builtin-strncmp -fno-builtin-strlen \
         -fno-builtin-memset -fno-builtin-memmove -fno-builtin-memcmp -fno-builtin-log \
         -fno-builtin-bzero -fno-builtin-strchr -fno-builtin-exit -fno-builtin-malloc \
         -fno-builtin-putc -fno-builtin-free -fno-builtin-memcpy -Wno-main -fno-builtin-printf \
         -fno-builtin-fprintf -fno-builtin-vprintf -I. -I../kernel -fno-stack-protector \
         -fno-pie -no-pie

LDFLAGS = -z max-page-size=4096

# Lista de programas
PROGS = \
    _cat \
    _echo \
    _forktest \
    _grep \
    _grind \
    _init \
    _kill \
    _ln \
    _ls \
    _mkdir \
    _rm \
    _sh \
    _stressfs \
    _usertests \
    _wc \
    _zombie

# Dependencias comunes
ULIB = ulib.o usys.o printf.o umalloc.o

# Regla para compilar cada programa
%: %.o $(ULIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilación de bibliotecas base
ulib.o: ulib.c
	$(CC) $(CFLAGS) -c -o $@ $<

usys.o: usys.S
	$(CC) $(CFLAGS) -c -o $@ $<

printf.o: printf.c
	$(CC) $(CFLAGS) -c -o $@ $<

umalloc.o: umalloc.c
	$(CC) $(CFLAGS) -c -o $@ $<

usys.S: usys.pl
	perl usys.pl > usys.S

# Regla para compilar todos los programas
all: $(PROGS)

# Limpieza
clean:
	rm -f *.o *.d $(PROGS)
