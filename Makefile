CC = clang
CFLAGS = -Wall -Wextra -pedantic 
TARGET = iris.exe
SRCS = main.c math.c neural.c
HEADERS = math.h neural.h
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-del /f $(TARGET) $(OBJS)

.PHONY: all clean