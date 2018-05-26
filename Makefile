##
## EPITECH PROJECT, 2017
## corewar
## File description:
## Makefile
##

NAME	=	42sh

CC	=	gcc

MAKE	=	/usr/bin/make

SRC_DIR	=	./srcs

BUILTINS	=$(SRC_DIR)/builtins

EXTRA		=$(SRC_DIR)/extra

HISTORY_DIR =	$(SRC_DIR)/history/

VAR_DIR	=	$(SRC_DIR)/variables/

LIB_DIR	=	./lib/my

UT_DIR	=	./tests

LIB_DIR	=	./lib/my

EXE	=	$(SRC_DIR)/main.c\
		$(SRC_DIR)/find_path.c\
		$(SRC_DIR)/error.c\
		$(BUILTINS)/cd.c\
		$(BUILTINS)/builtin.c\
		$(BUILTINS)/echo.c\
		$(BUILTINS)/alias.c\
		$(BUILTINS)/which.c\
		$(BUILTINS)/setenv.c\
		$(BUILTINS)/exit.c\
		$(BUILTINS)/env.c\
		$(BUILTINS)/unsetenv.c\
		$(SRC_DIR)/loop.c\
		$(SRC_DIR)/utils.c\
		$(SRC_DIR)/operator.c\
		$(SRC_DIR)/error_message.c\
		$(SRC_DIR)/command_and_priority.c\
		$(SRC_DIR)/differents_type_command.c\
		$(EXTRA)/globbing.c\
		$(EXTRA)/auto_complete.c\
		$(EXTRA)/prepare_auto_complete.c\
		$(EXTRA)/inhibitors.c\
		$(HISTORY_DIR)history.c\
		$(VAR_DIR)declare_variable.c\
		$(VAR_DIR)handle_variables.c\
		$(VAR_DIR)set_builtin.c\
		$(VAR_DIR)cwd.c\
		$(VAR_DIR)term.c\
		$(VAR_DIR)ignoreeof.c\
		$(VAR_DIR)special_variables.c\

OBJ	=	$(EXE:.c=.o)

UT 	= 	$(UT_DIR)/ut_error.c\
		$(UT_DIR)/ut_operator.c\
		$(UT_DIR)/ut_cd.c\
		$(UT_DIR)/ut_setenv.c\
		$(UT_DIR)/ut_path.c\



UT2	=	$(SRC_DIR)/find_path.c\
		$(SRC_DIR)/error.c\
		$(SRC_DIR)/cd.c\
		$(SRC_DIR)/builtin.c\
		$(SRC_DIR)/env.c\
		$(SRC_DIR)/loop.c\
		$(SRC_DIR)/setenv.c\
		$(SRC_DIR)/utils.c\
		$(SRC_DIR)/unsetenv.c\
		$(SRC_DIR)/operator.c\
		$(SRC_DIR)/error_message.c\
		$(SRC_DIR)/command_and_priority.c\
		$(SRC_DIR)/differents_type_command.c\

RM	=	rm -f

CFLAGS	=	##-Wall -Wextra

CPPFLAGS=	-I./includes/

LDFLAGS	=	-lncurses -L./lib/ -lmy

UT_FLAGS=	-lcriterion --coverage

INCLUDE	=	-I ./includes


all:		LIB $(NAME)

LIB:
		$(MAKE) -C $(LIB_DIR)

$(NAME):	LIB $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

tests_run:	LIB
		$(CC) $(INCLUDE) -o $(NAME) $(UT) $(UT2) -lcriterion -coverage  -L./lib/ -lmy
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
