EXE=hi
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))

CC=gcc
CFLAGS=-c -o

all:$(EXE)

$(EXE):$(OBJS)
	$(CC) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) $@ $^

.PHONY:clean
clean:
	rm $(OBJS) $(EXE)
