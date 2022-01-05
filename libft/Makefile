# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/20 17:28:41 by jboisser          #+#    #+#              #
#    Updated: 2022/01/05 16:01:51 by jboisser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_putchar.c ft_putstr.c ft_putstr_len.c ft_isalnum.c ft_isprint.c ft_memcmp.c \
					ft_putchar_fd.c ft_split.c ft_strlcat.c ft_strncmp.c ft_substr.c \
					ft_atoi.c ft_isalpha.c ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_memccpy.c \
					ft_memmove.c ft_putnbr_fd.c ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c ft_strcat.c ft_strcpy.c \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_memjoin.c ft_strcat_free.c \
					ft_strcmp.c ft_str_isdigit.c get_next_line.c get_next_line_utils.c \
					ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -g -Wall -Wextra -Werror -I.

NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
