OPTIMIZE = -O2

CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd

randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) randlibhw.c -shared -fPIC -o randlibhw.so
randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) randlibsw.c -shared -fPIC -o randlibsw.so
randmain: randmain.o randcpuid.o
	$(CC) $(CFLAGS) -c randcpuid.c -o randcpuid.o
	$(CC) $(CFLAGS) -c randmain.c -o randmain.o
	$(CC) $(CFLAGS) randmain.o randcpuid.o -ldl -Wl,-rpath=$(PWD) -o randmain
