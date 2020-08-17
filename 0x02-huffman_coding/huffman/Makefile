CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -ggdb3

SRC0 = huffman.c
OBJ0 = $(SRC0:.c=.o)
NAME0 = huffman

.PHONY: all clean oclean flcean re

all: $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)

clean:
	$(RM) *~ $(NAME0)

oclean:
	$(RM) $(OBJ0)

fclean: clean oclean

re: oclean all

huffman: huffman.h $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)
