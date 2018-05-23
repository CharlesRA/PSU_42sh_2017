##
## EPITECH PROJECT, 2017
## my_printf
## File description:
## unit_test_makefile
##

LIB_DIR	=	../lib/my

SRCS=	../srcs/

VAR_SRCS=	$(SRCS)variables/

HISTORY_SRCS=	$(SRCS)history/

BUILTINS=	$(SRCS)builtins/

PARSING=	$(SRCS)parsing/

ERRORS=		$(SRCS)errors/

ALL_DIR = 	$(SRCS)\
		$(VAR_SRCS)\
		$(HISTORY_SRCS)\
		$(BUILTINS)\
		$(PARSING)\
		$(ERRORS)\

CC	=	gcc

RM	=	rm -f

SRC_TEST=	$(VAR_SRCS)handle_variables.c\
		$(VAR_SRCS)cwd.c\
		$(HISTORY_SRCS)history.c\
		$(SRCS)loop.c\
		$(SRCS)utils.c\
		$(ERRORS)error.c\
		$(ERRORS)error_message.c\
		$(BUILTINS)cd.c\
		$(BUILTINS)setenv.c\
		$(BUILTINS)unsetenv.c\
		$(BUILTINS)builtin.c\
		$(BUILTINS)env.c\
		$(BUILTINS)alias.c\
		$(BUILTINS)echo.c\
		$(PARSING)operator.c\
		$(PARSING)command_and_priority.c\
		$(PARSING)differents_type_command.c\
		$(PARSING)find_path.c\
		ut_error.c\
		ut_operator.c\
		ut_cd.c\
		ut_setenv.c\
		ut_path.c\
		ut_history.c\
		ut_handle_variables.c\
#		ut_cwd.c\

OBJ	=	$(SRC_TEST:.c=.o)

OBJ_CRITERION	=	$(SRC_TEST:.c=.gcda)

GCNO_OBJ	=	$(SRC_TEST:.c=.gcno)

CFLAGS	=	-lcriterion --coverage

CPPFLAGS=	-I../includes/

LDFLAGS	=	-lcriterion --coverage -L../lib/ -lmy

NAME	=	42sh

all:	$(NAME)

LIB:
	$(MAKE) -C $(LIB_DIR)

$(NAME):	LIB $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	@./$(NAME)

see_coverage:
		gcov $(OBJ_CRITERION)
		cat *.c.gcov | less

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_CRITERION)
	@$(RM) $(GCNO_OBJ)
	@$(MAKE) clean -C $(LIB_DIR)

fclean:	clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIB_DIR)

re:	fclean all

.PHONY:	fclean all re clean see_coverage
