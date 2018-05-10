# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrouzeva <nrouzeva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 09:31:46 by nrouzeva          #+#    #+#              #
#    Updated: 2018/05/10 13:08:00 by nrouzeva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PROGRAM_malloc

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = inc
LFT_PATH = libft
INC_LFT_PATH = -I ./libft/libft/includes/ -I ./libft/printf/

SRC_NAME = malloc.c \
		   main.c \
		   show_alloc.c

OBJ_NAME = $(SRC_NAME:.c=.o)

CC = gcc -g
CFLAGS = #-Wextra -Wall -Werror #-fsanitize=address -fsanitize=undefined
LDFLAGS = -L$(LFT_PATH)
LDLIBS = -lft

RED=\033[1;31m
GREEN=\033[1;32m
NC=\033[0m

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LFT_PATH)
	@echo "$(GREEN)[✓]$(NC) Library built"
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INC_PATH) $(INC_LFT_PATH)
	@echo "$(GREEN)[✓]$(NC) Objects compiled"

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(RED)[-]$(NC) Objects cleaned"
	@make -C $(LFT_PATH) clean
	@echo "$(RED)[-]$(NC) Library cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[-]$(NC) Program clear"
	@make -C $(LFT_PATH) fclean

re:fclean
	@make
