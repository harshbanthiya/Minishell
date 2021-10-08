# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/15 16:17:24 by hbanthiy          #+#    #+#              #
#    Updated: 2021/10/08 13:49:27 by sfournie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

NAME	= libft.a

HDRS	= libft.h

SRCS	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_atoi.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_strchr.c ft_strlcpy.c ft_strlcat.c \
		ft_strdup.c ft_calloc.c ft_bzero.c ft_memset.c ft_memmove.c \
		ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_itoa.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		get_next_line.c ft_strcat.c ft_memdel.c ft_strsub.c ft_strsplit.c \
		ft_strclr.c ft_strcpy.c ft_strdel.c ft_strnew.c

OBJS	= $(SRCS:.c=.o)

IS_COMP	:=
%.o :  %.c
		@$(or $(IS_COMP),$(eval IS_COMP := :)echo "# Compiling libft objects files...")
		@$(CC) $(CFLAGS) -c $< -o $@

all		: $(NAME)

$(NAME) : $(HDRS) $(OBJS)
		@ar crs $(NAME) $(OBJS)
		# $(shell echo "libft library created")

clean	:
		@rm -rf $(OBJS)

fclean	: clean
		@rm -rf $(NAME)

re		: fclean all

.PHONY	: clean all re fclean bonus


# NAME=libft.a

# SRCS=*.c

# OBJECTS=*.o

# all: $(NAME)

# $(NAME):
# 	gcc -Wall -Wextra -Werror -c $(SRCS)
# 	ar -rc $(NAME) $(OBJECTS)
# 	ranlib $(NAME)

# clean:
# 	/bin/rm -f *.o

# fclean: clean
# 	/bin/rm -f $(NAME)

# re: fclean all
