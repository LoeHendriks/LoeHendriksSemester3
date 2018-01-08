CC = gcc
CFLAGS = -O2 -Wall -Werror 
LDFLAGS = -pthread -lrt

all: program_A program_B

program_A: program_A.c
	$(CC) $(CFLAGS) -o program_A program_A.c $(LDFLAGS)
program_B: program_B.c
	$(CC) $(CFLAGS) -o program_B program_B.c $(LDFLAGS)
	
clean:
	rm -f program_A program_B