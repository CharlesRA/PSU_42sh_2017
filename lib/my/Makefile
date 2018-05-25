##
## EPITECH PROJECT, 2018
## libmy.a
## File description:
## Makefile
##

SRC_DIR	=	.

LIB_DIR	=	..

SRC	=	$(SRC_DIR)/my_strlen.c	\
		$(SRC_DIR)/my_revstr.c	\
		$(SRC_DIR)/my_printf.c	\
		$(SRC_DIR)/add_delete_element.c\
		$(SRC_DIR)/binary_to_array.c\
		$(SRC_DIR)/get_next_line.c\
		$(SRC_DIR)/is_num.c\
		$(SRC_DIR)/my_array_dup.c\
		$(SRC_DIR)/my_array_len.c\
		$(SRC_DIR)/my_getnbr.c\
		$(SRC_DIR)/my_intlen.c\
		$(SRC_DIR)/my_print_binary.c\
		$(SRC_DIR)/my_put_digits.c\
		$(SRC_DIR)/my_strcmp.c\
		$(SRC_DIR)/my_strncmp.c\
		$(SRC_DIR)/my_strdup.c\
		$(SRC_DIR)/my_strdupcat.c\
		$(SRC_DIR)/my_strstr.c\
		$(SRC_DIR)/puts.c\
		$(SRC_DIR)/my_putchar.c\
		$(SRC_DIR)/my_print_hexa_with_caps.c\
		$(SRC_DIR)/my_print_hexa_without_caps.c\
		$(SRC_DIR)/my_compute_power_rec.c\
		$(SRC_DIR)/my_print_binary.c\
		$(SRC_DIR)/my_intlen.c\
		$(SRC_DIR)/my_print_percent.c\
		$(SRC_DIR)/my_print_pointers.c\
		$(SRC_DIR)/my_put_integrer.c\
		$(SRC_DIR)/my_print_string_witherror.c\
		$(SRC_DIR)/my_put_octal.c\
		$(SRC_DIR)/my_print_unsigned_number.c\
		$(SRC_DIR)/read_list.c\
		$(SRC_DIR)/my_binary_to_int.c\
		$(SRC_DIR)/my_str_to_word_array.c\
		$(SRC_DIR)/my_char_is_alpha_num.c\
		$(SRC_DIR)/find_line_env.c\
		$(SRC_DIR)/my_strcat.c\
		$(SRC_DIR)/my_strlen.c\
		$(SRC_DIR)/path_to_array.c\
		$(SRC_DIR)/my_strdupcat.c\
		$(SRC_DIR)/my_strstr.c\
		$(SRC_DIR)/my_realloc.c\
		$(SRC_DIR)/puts.c\
		$(SRC_DIR)/find_line_env.c\
		$(SRC_DIR)/my_strdup.c\
		$(SRC_DIR)/my_strcmp.c\
		$(SRC_DIR)/my_array_len.c\
		$(SRC_DIR)/puts_error.c\
		$(SRC_DIR)/my_array_free.c\
		$(SRC_DIR)/check_string.c\

AR	=	ar rc

CC	=	gcc

CFLAGS	=	#-Wall -Wextra -Werror

CPPFLAGS=	-I../../includes/

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	$(AR) $(NAME) $(OBJ)
	cp $(NAME) $(LIB_DIR)
	$(RM) $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(LIB_DIR)/$(NAME)

.PHONY: fclean all clean
