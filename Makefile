# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 10:03:15 by sasaicic          #+#    #+#              #
#    Updated: 2021/12/18 13:00:44 by sasaicic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname -s)
NAME = minishell
CC = gcc 
CFLAGS = -g -Wall -Wextra -Werror
SRCS =	main.c get_tokens.c  free.c lst_utils.c exit.c command.c \
		handle_operators.c handle_redirection.c clear.c echo.c utils.c \
		execute.c get_path.c parser.c expansion.c var.c directory.c exit_shell.c \
		environment.c plug_pipes.c handle_heredoc.c signal.c handle_expansion.c \
		parsing_utils.c handle_quote.c colons.c buffer_checks.c set_io_exec.c \
		utils_2.c utils_3.c
INC = -Iincludes -Ilibft
OBJS = $(SRCS:.c=.o)
D_LIBFT = ./libft/
LIBFT = $(D_LIBFT)libft.a
LDFLAGS = -lreadline -L$(D_LIBFT) -lft
READLINE_PATH = $(shell brew --prefix readline)

ifeq ($(OS), Darwin)
	INC += -I $(READLINE_PATH)/include
	LDFLAGS += -L$(READLINE_PATH)/lib
endif

vpath %.c srcs srcs/lexer srcs/parser srcs/execution srcs/command srcs/builtins srcs/utils srcs/piping srcs/variables
vpath %.o obj
vpath %.h includes libft

all: $(OBJS)
	$(MAKE) -C $(D_LIBFT)
	$(CC) $(CFLAGS) $(addprefix obj/, $(OBJS)) $(LDFLAGS) -o $(NAME)

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

run: all 
	./$(NAME)

fsanitize: all 
	$(CC) -fsanitize=address $(CFLAGS) $(addprefix obj/, $(OBJS)) -lreadline -L$(D_LIBFT) -lft -o $(NAME)

gdb: all
	gdb -q ./$(NAME)

val: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=sup_readline.val ./$(NAME)

vgdb: all
	valgrind --leak-check=full --show-leak-kinds=all --vgdb=yes --vgdb-error=0 ./$(NAME)
