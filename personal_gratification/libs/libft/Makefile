# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/01 12:20:56 by cbaek             #+#    #+#              #
#    Updated: 2020/09/18 20:44:00 by cbaek            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		ft_strndup.c
SRCS_BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
SRCS_ADDITIONAL = ft_uitoa_base.c ft_ultoa_base.c
OBJS = $(SRCS:%.c=%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)
OBJS_ADDITIONAL = $(SRCS_ADDITIONAL:%.c=%.o)

%.o: %.c
	$(CC) -c $(CFLAGS) -c $< -o ${<:.c=.o}
$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)
all: $(NAME)
bonus: $(NAME) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)
additional: $(NAME) $(OBJS_BONUS) $(OBJS_ADDITIONAL)
	ar rcs $(NAME) $(OBJS_BONUS) $(OBJS_ADDITIONAL)
clean:
	rm -f ${OBJS} $(OBJS_BONUS) $(OBJS_ADDITIONAL)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all bonus clean fclean re
