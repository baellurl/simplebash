CC = gcc
CFLAGS = -std=c11 -Werror -Wextra -Wall
TARGET = s21_grep

all: $(TARGET)

$(TARGET): s21_grep.c 
		$(CC) $(CFLAGS) s21_grep.c parser.c -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
