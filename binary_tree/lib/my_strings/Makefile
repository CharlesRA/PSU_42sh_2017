##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## compile and copy the library
##

CC	=	gcc -W -Wall -Wextra -pedantic

SRC	=	$(wildcard *.c)

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy_strings.a

HEAD	=	my_strings.h

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../
	cp $(HEAD) ../../include/

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME) ../$(NAME)

re:	fclean all
