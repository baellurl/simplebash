CC = gcc
CFLAGS = -std=c11 -Werror -Wextra -Wall
TARGET = s21_cat

all: $(TARGET) 

$(TARGET): s21_cat.c 
		$(CC) $(CFLAGS) s21_cat.c arg_parser.c -o $(TARGET)

clean:
	rm -f $(TARGET) *.o