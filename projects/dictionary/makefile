CC = gcc
CFLAGS = -Wall -Wextra -Iinc -Iserver -Iclient
LDFLAGS = -pthread

SERVER_SRC = server/server.c server/*.c src/*.c
CLIENT_SRC = client/client.c client/*.c src/*.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

SERVER_EXEC = server/server
CLIENT_EXEC = client/client

.PHONY: all clean

all: $(SERVER_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(CLIENT_EXEC): $(CLIENT_OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(SERVER_OBJ) $(CLIENT_OBJ) $(SERVER_EXEC) $(CLIENT_EXEC)
