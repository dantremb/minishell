# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 23:33:38 by root              #+#    #+#              #
#    Updated: 2022/12/09 11:28:47 by dantremb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom du Projet
NAME = minishell

# Flags
AR = ar
CC = gcc
ARFLAGS = rcs
CFLAGS = -Wall -Wextra -Werror -g
RLFLAGS = -lreadline -lncurses

# Includes
LIBFT = libs/libft/libft.a
LIBFT_PATH = libs/libft/
READLINE = libs/readline/libreadline.a
READHISTORY = libs/readline/libhistory.a

# Sources files
S = srcs/
SRCS_FILES =	minishell.c \
				validation.c \
				parsing.c \
				builtins.c \
				engine.c \
				execute.c \
				tokens.c \
				signals.c \

SRCS = $(addprefix $S, $(SRCS_FILES))

# Objects conversion
O = objs/
OBJS= $(SRCS:$S%=$O%.o)
$O%.o: $S%
	@printf "$R■$W"
	@$(CC) $(CFLAGS) -c $< -o $@

# Main rule
all: signature init $(NAME)
	@echo "$G\n$(NAME) Compiled!$W"

# Initialise librairies and making objs folder
init:
	@mkdir -p $O
	@echo "$GLibrary's initialization$W"
	@$(MAKE) -s -C $(LIBFT_PATH)
	@printf "$CCreating $(NAME)\n$W"

# Creating  executable
$(NAME): $(OBJS)
	@$(CC) -o $@ $^ $(CFLAGS) $(RLFLAGS) $(READLINE) $(READHISTORY) $(LIBFT)

# Cleaning
REMOVE = rm -rf

clean:
	@$(REMOVE) $O
	@$(MAKE) -s clean -C $(LIBFT_PATH)
	@$(REMOVE) minishell.dSYM

fclean: clean
	@$(REMOVE) $(NAME)
	@$(MAKE) -s fclean -C $(LIBFT_PATH)

re:	fclean all

# Utilities
COMMIT = $(shell date "+%d %B %T")
git:
	@git add .
	@git commit -m "$(COMMIT)"
	@git push

R = $(shell tput -Txterm setaf 1)
G = $(shell tput -Txterm setaf 2)
C = $(shell tput -Txterm setaf 6)
W = $(shell tput -Txterm setaf 7)

signature:
	@echo "\n$G+---+---+---+---+---+---+---+---+"
	@echo "$G|$C	$(NAME) by Dantremb	$G|"
	@echo "$G+---+---+---+---+---+---+---+---+"

t:
	valgrind --leak-check=summary --trace-children=yes ./$(NAME)

tt:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(NAME)

ttt:
	valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=yes --trace-children=yes ./$(NAME)