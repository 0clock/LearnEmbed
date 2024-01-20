# Makefile

# 编译器
CC = gcc

# 编译选项
CFLAGS = -Wall -Werror

# 目标文件夹
BUILD_DIR = build

# 源文件夹
SRC_DIR = src
INC_DIR = inc
SERVER_DIR = server
CLIENT_DIR = client

# 服务器和客户端的可执行文件名
SERVER_EXE = $(BUILD_DIR)/server
CLIENT_EXE = $(BUILD_DIR)/client

# 共享的源文件
COMMON_SRC = $(wildcard $(SRC_DIR)/*.c)

# 服务器和客户端的源文件
SERVER_SRC = $(SERVER_DIR)/server.c
CLIENT_SRC = $(CLIENT_DIR)/client.c

# 服务器和客户端的目标文件
SERVER_OBJ = $(BUILD_DIR)/server.o
CLIENT_OBJ = $(BUILD_DIR)/client.o
COMMON_OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(COMMON_SRC))

# 创建 build 目录
$(shell mkdir -p $(BUILD_DIR))

# 所有的目标
all: server client

# 服务器目标
server: $(SERVER_EXE)

$(SERVER_EXE): $(SERVER_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# 客户端目标
client: $(CLIENT_EXE)

$(CLIENT_EXE): $(CLIENT_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# 公共源文件目标
$(COMMON_OBJ): $(COMMON_SRC)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# 清理目标
clean:
	rm -rf $(BUILD_DIR)/*.o $(SERVER_EXE) $(CLIENT_EXE)

# 伪目标，防止与文件名冲突
.PHONY: all server client clean
