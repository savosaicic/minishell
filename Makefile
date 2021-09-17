NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SRCS = main.c get_tokens.c  utils_tab.c exit.c command.c clear.c write_command.c
INC = -Iincludes -Ilibft
OBJS = $(SRCS:.c=.o)
LIBFT = libft.a
D_LIBFT = ./libft

vpath %.c srcs srcs/lexer srcs/utils srcs/parser srcs/command srcs/error
vpath %.o obj
vpath %.h includes libft

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(addprefix obj/, $(OBJS)) -lreadline -L$(D_LIBFT) -lft -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C $(D_LIBFT)

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
