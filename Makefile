NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SRCS = main.c get_tokens.c  utils_tab.c exit.c command.c handle_operators.c handle_redirection.c \
		clear.c echo.c utils.c execute.c get_path.c parser.c expansion.c export.c env.c \
		environment.c
INC = -Iincludes -Ilibft
OBJS = $(SRCS:.c=.o)
D_LIBFT = ./libft/
LIBFT = $(D_LIBFT)libft.a

vpath %.c srcs srcs/lexer srcs/parser srcs/execution srcs/command srcs/builtins srcs/utils
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

run: all 
	./$(NAME)

clean:
	make clean -C $(D_LIBFT)
	$(RM) -rf obj

fclean: clean
	$(MAKE) fclean -C $(D_LIBFT)
	$(RM) -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re

fsanitize: all 
	$(CC) -fsanitize=address $(CFLAGS) $(addprefix obj/, $(OBJS)) -lreadline -L$(D_LIBFT) -lft -o $(NAME)
