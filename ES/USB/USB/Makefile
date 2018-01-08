PRODUCT=USB

CFLAGS=-O2 -Wall -Werror -lusb-1.0

LIBUSB = `pkg-config libusb-1.0 --cflags --libs`
LIBS = $(LIBUSB)

SOURCES=$(wildcard *.c)

HEADERS=$(wildcard *.h)

CC=arm-linux-gcc

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS) Makefile
	@$(CC) $(CFLAGS) $(SOURCES) -o $@ $(LIBS)

clean:
	@rm -rf $(PRODUCT)