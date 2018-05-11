##
## EPITECH PROJECT, 2017
## corewar
## File description:
## Makefile
##

NAME	=	42sh

CC	=	gcc -g3

MAKE	=	/usr/bin/make

SRC_DIR	=	./srcs

LIB_DIR	=	./lib/my

UT_DIR	=	./tests

LIB_DIR	=	./lib/my

BUILTINS=	./srcs/builtins

PARSING=	./srcs/parsing

ERRORS=		./srcs/errors

EXE	=	$(SRC_DIR)/main.c\
		$(SRC_DIR)/loop.c\
		$(SRC_DIR)/utils.c\
		$(ERRORS)/error.c\
		$(ERRORS)/error_message.c\
		$(BUILTINS)/cd.c\
		$(BUILTINS)/setenv.c\
		$(BUILTINS)/unsetenv.c\
		$(BUILTINS)/builtin.c\
		$(BUILTINS)/env.c\
		$(BUILTINS)/alias.c\
		$(PARSING)/operator.c\
		$(PARSING)/command_and_priority.c\
		$(PARSING)/differents_type_command.c\
		$(PARSING)/find_path.c\


OBJ	=	$(EXE:.c=.o)

UT 	=	$(UT_DIR)/ut_command.c\
		# $(UT_DIR)/ut_error.c\
		# $(UT_DIR)/ut_operator.c\
		# $(UT_DIR)/ut_setenv.c\
		# $(UT_DIR)/ut_path.c\

UT2	=	$(SRC_DIR)/loop.c\
		$(SRC_DIR)/utils.c\
		$(ERRORS)/error.c\
		$(ERRORS)/error_message.c\
		$(BUILTINS)/cd.c\
		$(BUILTINS)/setenv.c\
		$(BUILTINS)/unsetenv.c\
		$(BUILTINS)/builtin.c\
		$(BUILTINS)/env.c\
		$(PARSING)/operator.c\
		$(PARSING)/command_and_priority.c\
		$(PARSING)/differents_type_command.c\
		$(PARSING)/find_path.c\


RM	=	rm -f

CFLAGS	=	-g3 ##-Wall -Wextra

CPPFLAGS=	-I./includes/

LDFLAGS	=	-L./lib/ -lmy

UT_FLAGS=	-lcriterion --coverage

INCLUDE	=	-I ./includes


all:		LIB $(NAME)

LIB:
		$(MAKE) -C $(LIB_DIR)

debug: fclean debug2

debug2: CFLAGS += -g3
debug2: MAKE	+= debug
debug2:	all

$(NAME):	LIB $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

tests_run:	LIB
		$(CC) -g3 $(INCLUDE) -o $(NAME) $(UT) $(UT2) -lcriterion -coverage  -L./lib/ -lmy
		./$(NAME)

clean:
		$(MAKE) clean -C $(LIB_DIR)
		$(RM) $(OBJ)

ut_clean:
		rm *gc*

fclean:		clean
		$(MAKE) fclean -C $(LIB_DIR)
		$(RM) $(NAME)

re:		fclean all

.PHONY:		re all fclean clean
