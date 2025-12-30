CC = gcc
CFLAGS = -Wall -I./FunctionFolder

SRCS = main.c FunctionFolder/case1.c FunctionFolder/case2.c FunctionFolder/generalf.c FunctionFolder/globalvariables.c
OBJS = $(SRCS:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
        $(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
        $(CC) $(CFLAGS) -c $< -o $@

clean:
        rm -f *.o FunctionFolder/*.o

run: #Don't run the file with this command
        ./$(TARGET)

.PHONY: all clean