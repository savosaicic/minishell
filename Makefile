NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SRCS = main.c get_tokens.c parser.c get_cmd_path.c get_path.c parser2.c exec.c error.c \
		clear_cmd_struct.c utils.c clear_token_struct.c handle_operators.c
INC = -Iincludes -Ilibft
OBJS = $(SRCS:.c=.o)
D_LIBFT = ./libft
LIBFT = $(D_LIBFT)libft.a

vpath %.c srcs srcs/lexer srcs/utils srcs/parser srcs/exec srcs/error
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
