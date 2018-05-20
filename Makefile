# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrouzeva <nrouzeva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/02 09:31:46 by nrouzeva          #+#    #+#              #
#    Updated: 2018/05/20 21:03:19 by nrouzeva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = PROGRAM_MALLOC #libft_malloc_$(HOSTTYPE).so

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = inc
LFT_PATH = libft
INC_LFT_PATH = -I ./libft/libft/includes/ -I ./libft/printf/
LINK_NAME = libft_malloc.so

SRC_NAME = malloc.c \
		   show_alloc.c \
		   free.c \
		   defrag_mem.c \
		   realloc.c \
		   alloc_finder.c \
		   main.c

OBJ_NAME = $(SRC_NAME:.c=.o)

CC = gcc -g
CFLAGS = #-Wextra -Wall -Werror -g #-fsanitize=address -fsanitize=undefined
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
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS) #-shared
	@ln -sF $(NAME) $(LINK_NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_PATH) $(INC_LFT_PATH) 
	@echo "$(GREEN)[✓]$(NC) Source compiled : $<"

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(RED)[-]$(NC) Objects cleaned"
	@make -C $(LFT_PATH) clean
	@echo "$(RED)[-]$(NC) Library cleaned"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)[-]$(NC) Program clear"
	@make -C $(LFT_PATH) fclean
	@echo "$(RED)[-]$(NC) Libft clear"
	@rm -rf $(LINK_NAME)
	@echo "$(RED)[-]$(NC) Link clear"

re:fclean
	@make
