NAME 	=	minishell

SRC		=   main.c test.c \

SRCS 	= 	$(addprefix $(D_SRCS)/, $(SRC))

D_SRCS	=	./srcs
D_LIBFT	=	./libft
INC		=	./includes

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	
RM		=	rm -rf

all:		$(OBJS)
			make -C $(D_LIBFT)
			$(CC) $(OBJS) $(CFLAGS) -I$(INC) -I$(D_LIBFT) -lreadline -L$(D_LIBFT) -lft -o $(NAME)

clean:		
			make clean -C $(D_LIBFT)
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C $(D_LIBFT)
			$(RM) $(NAME)

re:			fclean
			make re -C $(D_LIBFT)
			make

%.o:%.c
			@gcc $(CFLAGS) -c $< -o $@ -I$(INC) -I$(D_LIBFT)

.PHONY: all fclean clean re


