##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

NAME	=	42sh

NAMET	=	unit_tests

CC	=	gcc

SRC	=	src/globing.c \
		src/builtin.c \
		src/commands/commands_built_in.c \
		src/commands/commands_cd.c \
		src/commands/commands_env.c \
		src/commands/commands_set_unsetenv.c \
		src/commands/operator.c \
		src/errors.c \
		src/exit.c \
		src/history/history.c \
		src/io_redirections.c \
		src/main.c \
		src/minishell.c \
		src/pipes.c \
		src/program.c \
		src/program_path.c \
		src/prompt.c \
		src/signals.c \
		src/tree/tree.c \
		src/tree/make_tree.c \
		src/tree/lexer/lexer.c \
		src/tree/lexer/lexer_add_node.c \
		src/tree/lexer/lexer_check_type.c \
		src/tree/rpn.c \
		src/tree/rpn_aux.c \
		src/var.c \
		src/variables/cwd.c \
		src/variables/declare_variable.c \
		src/variables/handle_variables.c \
		src/variables/set_builtin.c \

SRCT	=	tests/tests.c

CFLAGS	=	-W -Wall -Wextra -Wno-unused-variable -pedantic -Wno-unused-parameter

CPPFLAGS=	-I./includes/

OBJ	=	$(SRC:.c=.o)

OBJT	=	tests.o

LIB_DIR	=	lib/

LDFLAGS	=	-L$(LIB_DIR) -lmy -lmy_strings -lncurses

all:	$(NAME)

lib_make:
	make -C $(LIB_DIR)my
	make -C $(LIB_DIR)my_strings

$(NAME):	lib_make $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

tests_run:	lib_make
	$(CC) --coverage -c $(SRCT)
	$(CC) $(CFLAGS) $(OBJT) -lcriterion -lgcov -o $(NAMET) $(LDFLAGS)
	./$(NAMET)

clean:
	make clean -C $(LIB_DIR)my
	make clean -C $(LIB_DIR)my_strings
	$(RM) $(OBJ) $(OBJT)
	$(RM) *.gcno *.gcda

fclean:	clean
	make fclean -C $(LIB_DIR)my
	make fclean -C $(LIB_DIR)my_strings
	$(RM) $(NAME) $(NAMET)

re:	fclean all

.PHONY: all clean fclean re tests_run lib_make
