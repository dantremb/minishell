# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 23:33:38 by root              #+#    #+#              #
#    Updated: 2022/06/21 22:05:11 by dantremb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = includes/libft/libft.a
LIBFT_PATH = includes/libft/
READLINE = includes/readline/libreadline.a

SRCS_FILES = minishell.c
SRCS_PATH = srcs/
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

AR = ar
CC = gcc

ARFLAGS = rcs
CFLAGS = -Wall -Wextra -Werror -g


REMOVE = rm -rf
COMMIT = $(shell date "+%d %B %T")

OBJS= $(SRCS:%.c=%.o)
%.o: %.c
	@printf "-"
	@$(CC) $(CFLAGS) -o $@ -c $<

all: init $(NAME)
	@echo "> Done!."
	@echo "$(NAME) Compiled!"

init:
	@echo "Preparing Libft"
	@$(MAKE) -s -C $(LIBFT_PATH)
	@echo "Preparing $(NAME)"
	@printf "Compiling -"

$(NAME): $(OBJS)
	@$(CC) -o $@ $^ $(LIBFT) $(CFLAGS) $(READLINE) -lreadline -lncurses
clean:
	@$(REMOVE) $(OBJS)
	@@$(MAKE) -s clean -C $(LIBFT_PATH)
fclean: clean
	@$(REMOVE) $(NAME)
	@$(MAKE) -s fclean -C $(LIBFT_PATH)

re:	fclean all

git:
	@git add .
	@git commit -m "$(COMMIT)"
	@git push
