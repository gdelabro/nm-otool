# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdelabro <gdelabro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/15 15:37:25 by gdelabro          #+#    #+#              #
#    Updated: 2019/01/29 18:37:03 by gdelabro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1 = ft_nm
NAME_2 = ft_otool

SRC_PATH_1 = nm/src
SRC_NAME_1 = main.c handle_64.c nm.c print_symbols.c fill_sections_64.c\
										handle_32.c nm.c fill_sections_32.c fill_sections_fat.c\
										handle_fat.c swap.c free_structs.c handle_ar.c\

SRC_PATH_2 = otool/src

SRC_NAME_2 = \

OBJ_PATH_1 = nm/obj
OBJ_NAME_1 = $(SRC_NAME_1:.c=.o)

OBJ_PATH_2 = otool/obj
OBJ_NAME_2 = $(SRC_NAME_2:.c=.o)

CC = clang
CFLAGS = #-Wall -Werror -Wextra

CPPFLAGS = -I nm/src -I otool/src -I includes -I ft_printf/includes

LDFLAGS = -L libft
LDLIBS = -lftprintf
LIB = libft/libftprintf.a

SRC_1 = $(addprefix $(SRC_PATH_1)/,$(SRC_NAME_1))
OBJ_1 = $(addprefix $(OBJ_PATH_1)/,$(OBJ_NAME_1))

SRC_2 = $(addprefix $(SRC_PATH_2)/,$(SRC_NAME_2))
OBJ_2 = $(addprefix $(OBJ_PATH_2)/,$(OBJ_NAME_2))

all: $(LIB) $(NAME_1) #$(NAME_2)

$(LIB):
	@make -C libft

$(NAME_1): $(OBJ_1)
	@printf "\n"
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "Compilation of \033[34;1m$@\033[0;1m: [\033[1;32mOK\033[0;1m]"

$(NAME_2): $(OBJ_2)
	@printf "\n"
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "Compilation of \033[31;1m$@\033[0;1m: [\033[1;32mOK\033[0;1m]"

$(OBJ_PATH_1)/%.o: $(SRC_PATH_1)/%.c
	@printf "\033[34;1m| \033[0;1m"
	@mkdir $(OBJ_PATH_1) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

$(OBJ_PATH_2)/%.o: $(SRC_PATH_2)/%.c
	@printf "\033[31;1m| \033[0;1m"
	@mkdir $(OBJ_PATH_2) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

clean:
	@make -C libft clean
	@rm -rf $(OBJ_1)
	@rm -rf $(OBJ_2)
	@rm -rf $(OBJ_PATH_1)
	@rm -rf $(OBJ_PATH_2)
	@echo "\033[34;1m$(NAME_1)\033[0;1m: objects deleted"
	@echo "\033[31;1m$(NAME_2)\033[0;1m: objects deleted"

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME_1)
	@rm -rf $(NAME_2)
	@echo "\033[34;1m$(NAME_1)\033[0;1m: $(NAME_1) deleted"
	@echo "\033[31;1m$(NAME_2)\033[0;1m: $(NAME_2) deleted"

re: fclean all

.PHONY: all clean fclean re
