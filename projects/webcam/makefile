# 编译器
CC = g++
# 可执行文件名
TARGET = webcam
# 源文件目录
SRCDIR = src
# 目标文件目录
BUILDDIR = build
# 获取源文件列表
SRCS = $(wildcard $(SRCDIR)/*.cpp)
# 生成目标文件列表
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
# 需要链接的动态库
DLIBS = -lopencv_core -lopencv_videoio -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(DLIBS)

# 编译每个源文件生成目标文件
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -o $@ -c $<

# 清理生成的目标文件和可执行文件
clean:
	rm -rf $(TARGET) $(BUILDDIR)/*.o

# 声明 clean 为伪目标，避免与同名文件冲突
.PHONY: clean
