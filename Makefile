NAME = minishell
CC = gcc
CFLAGS = 
SRCS = main.c get_tokens.c list_utils.c list_utils2.c parser.c error.c
INC = -Iincludes -Ilibft
OBJS = $(SRCS:.c=.o)
LIBFT = libft.a
D_LIBFT = ./libft

vpath %.c srcs srcs/lexer srcs/utils srcs/parser srcs/error
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
