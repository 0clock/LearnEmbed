# Makefile for the chat project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror


# Directories
INC_DIR = inc
SERVER_DIR = server
CLIENT_DIR = client
INC_FLAGS = -I$(INC_DIR)

# Source files
SERVER_SRC = $(wildcard $(SERVER_DIR)/*.c)
CLIENT_SRC = $(wildcard $(CLIENT_DIR)/*.c)

# Object files
SERVER_OBJ = $(patsubst $(SERVER_DIR)/%.c, $(SERVER_DIR)/%.o, $(SERVER_SRC))
CLIENT_OBJ = $(patsubst $(CLIENT_DIR)/%.c, $(CLIENT_DIR)/%.o, $(CLIENT_SRC))

# Targets
all: server client

server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
$(SERVER_DIR)/%.o: $(SERVER_DIR)/%.c $(INC_DIR)/common.h
	$(CC) $(CFLAGS) $(INC_FLAGS) -c -o $@ $<

$(CLIENT_DIR)/%.o: $(CLIENT_DIR)/%.c $(INC_DIR)/common.h
	$(CC) $(CFLAGS) $(INC_FLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(SERVER_DIR)/*.o $(CLIENT_DIR)/*.o server client
