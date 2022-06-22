# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 23:33:38 by root              #+#    #+#              #
#    Updated: 2022/06/20 23:59:23 by dantremb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de la librairie.
NAME = libft.a

# Fichiers sources.
SRCS_FILES = ft_isascii.c ft_strlcpy.c ft_toupper.c ft_memchr.c ft_memmove.c \
		ft_putnbr_fd.c ft_putendl_fd.c ft_lstmap.c ft_lstiter.c ft_lstclear.c \
		ft_strlen.c ft_putchar_fd.c ft_split.c ft_lstadd_front.c ft_strchr.c \
		ft_bzero.c ft_calloc.c ft_memcmp.c ft_strnstr.c ft_lstnew.c ft_itoa.c\
		ft_lstdelone.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_atoi.c \
		ft_strcat.c ft_isalnum.c ft_putchar.c ft_memcpy.c ft_putstr_fd.c \
		ft_striteri.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c \
		ft_strncmp.c ft_isalpha.c ft_strlcat.c ft_tolower.c ft_memset.c \
		ft_isdigit.c ft_putstr.c ft_strrchr.c ft_isprint.c ft_strdup.c \
		ft_atoli.c ft_get_next_line.c ft_printf.c ft_printf_utils.c

# Ajoute le noms du dossier en avant de chaque sources.
SRCS_PATH = srcs/
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))

# Compilateurs
AR = ar
CC = gcc

# Flags
ARFLAGS = rcs
CFLAGS = -Wall -Wextra -Werror -g

# Macros
REMOVE = rm -rf
COMMIT = $(shell date "+%d %B %T")

# Transforme les fichiers .c en fichiers .o
# La premiere utilise le contenu de la 2e pour compiler.
# J'imprime un tiret (sans newline) pour créer ma ligne de progression.
OBJS= $(SRCS:%.c=%.o)
%.o: %.c
	@printf "-"
	@$(CC) $(CFLAGS) -c -o $@ $<
	
# On appel la commande INIT et NAME puis on imprime le message final.
all: init $(NAME)
	@echo "> Done!."
	@echo "$(NAME) Compiled!"

# On imprime le début de la compilation à l'écran (sans newline).
init:
	@printf "Compiling -"

# On appel la création des OBJS et ensuite on compile la librairie.
$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^

# Commande de nettoyage.
clean:
	@$(REMOVE) $(OBJS)
fclean: clean
	@$(REMOVE) $(NAME)

# On nettoie et recompile.
re:	fclean all

# On peut choisir le nom de commit avec "make git COMMIT="
git:
	git add .
	git commit -m "$(COMMIT)"
	git push
