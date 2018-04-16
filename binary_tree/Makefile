##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

NAME	=	mysh

NAMET	=	unit_tests

CC	=	gcc -Iinclude/

SRC	=	src/main.c \
		src/minishell.c \
		src/display.c \
		src/program.c \
		src/tree.c \
		src/make_tree.c \
		src/lexer/lexer.c \
		src/lexer/lexer_add_node.c \
		src/lexer/lexer_check_type.c \
		src/rpn.c \
		src/rpn_aux.c \
		src/commands/commands_built_in.c \
		src/commands/commands_cd.c \
		src/commands/commands_env.c \
		src/commands/commands_set_unsetenv.c \
		src/errors.c \
		src/exit.c \
		src/signals.c \
		src/var.c

SRCT	=	tests/tests.c

CFLAGS	=	-W -Wall -Wextra -pedantic

OBJ	=	$(SRC:.c=.o)

OBJT	=	tests.o

LIB_DIR	=	lib/

LDFLAGS	=	-L$(LIB_DIR) -lmy -lmy_strings -lmy_files

all:	$(NAME)

lib_make:
	make -C $(LIB_DIR)my
	make -C $(LIB_DIR)my_strings
	make -C $(LIB_DIR)my_files

$(NAME):	lib_make $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LDFLAGS)

tests_run:	lib_make
	$(CC) --coverage -c $(SRCT)
	$(CC) $(CFLAGS) $(OBJT) -lcriterion -lgcov -o $(NAMET) $(LDFLAGS)
	./$(NAMET)

clean:
	make clean -C $(LIB_DIR)my
	make clean -C $(LIB_DIR)my_strings
	make clean -C $(LIB_DIR)my_files
	$(RM) $(OBJ) $(OBJT)
	$(RM) *.gcno *.gcda

fclean:	clean
	make fclean -C $(LIB_DIR)my
	make fclean -C $(LIB_DIR)my_strings
	make fclean -C $(LIB_DIR)my_files
	$(RM) $(NAME) $(NAMET)

re:	fclean all

.PHONY: all, clean, fclean, re, tests_run, lib_make
