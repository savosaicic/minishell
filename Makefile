# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/06 13:16:58 by sasaicic          #+#    #+#              #
#    Updated: 2021/09/06 13:17:38 by sasaicic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c test.c
INC = -Iincludes -Ilibft
OBJS = $(SRCS:.c=.o)
LIBFT = libft.a
D_LIBFT = ./libft

vpath %.c srcs
vpath %.o obj
vpath %.h includes libft

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(addprefix obj/, $(OBJS)) -lreadline -L$(D_LIBFT) -lft -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(D_LIBFT)

$(OBJS): %.o: %.c
	mkdir -p obj
	$(CC) -c $(CFLAGS) $< $(INC) -o obj/$@

clean:
	make clean -C $(D_LIBFT)
	$(RM) -rf obj

fclean: clean
	$(MAKE) fclean -C $(D_LIBFT)
	$(RM) -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
