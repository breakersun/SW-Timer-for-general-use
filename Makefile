CFLAGS=-O -Wuninitialized -Werror -I.
CC=GCC

# all: example-codelock example-buffer example-small
all: main

example-codelock: example-codelock.c hsm.c demo_process.c times.c

example-buffer: example-buffer.c

example-small: example-small.c

example-yield-with-time: example-yield-with-time.c

main: main.c SoftTimer.c
