CFLAGS=-Wall -Werror -pedantic  -ggdb -O0 -std=c++98 -Iproduct 
LDFLAGS=-pthread 

TEST_LIBS=-lgtest -lgmock -lgmock_main -lpthread

SOURCES=$(wildcard Product/*.cpp)
HEADERS=$(wildcard Product/*.h)

TEST_SOURCES=$(wildcard Test/*.cpp)
SOURCES_INC=-I./Product

CC=g++

.phony: all clean

all: SluiceControl SluiceTest

SluiceControl: $(SOURCES) $(HEADERS) Makefile 
	@$(CC) $(CFLAGS_NORMAL) UI.cpp $(SOURCES) -o $@ $(LDFLAGS)
	
	
SluiceTest: $(TEST_SOURCES) $(SOURCES) $(HEADERS) Makefile
	@$(CC) $(CFLAGS_NORMAL) $(TEST_SOURCES) $(SOURCES) $(SOURCES_INC) -o $@ $(TEST_LIBS)

clean:
	@rm -rf SluiceTest
