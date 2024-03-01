CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDLIBS = -lavformat -lavcodec -lavutil -lswscale
INCLUDES = -I/usr/include/x86_64-linux-gnu/libavformat/
LIBS_DIR = -L/usr/lib/x86_64-linux-gnu/
SRC = main.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = my_webcam

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
    $(CC) $(CFLAGS) $(INCLUDES) $(LIBS_DIR) -o $@ $^ $(LDLIBS)

%.o: %.c
    $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
    rm -f $(OBJ) $(EXECUTABLE)
