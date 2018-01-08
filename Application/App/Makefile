CC = arm-linux-gcc
CFLAGS = -O2 -Wall -Werror -lusb-1.0
LDFLAGS = -pthread -lrt

all: DaemonProgram ReadingProgram

DaemonProgram: DeamonProgram.c
	$(CC) $(CFLAGS) -o DeamonProgram DeamonProgram.c $(LDFLAGS)
ReadingProgram: ReadingProgram.c
	$(CC) $(CFLAGS) -o ReadingProgram.cgi ReadingProgram.c $(LDFLAGS)
	
clean:
	rm -f DaemonProgram ReadingProgram
