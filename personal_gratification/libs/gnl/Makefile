# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/11 13:10:54 by cbaek             #+#    #+#              #
#    Updated: 2020/12/11 15:34:05 by cbaek            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libgnl.a
CC		= gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

INCS	=	-I./
SRCS	=	./get_next_line.c ./get_next_line_utils.c
OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)
$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)
clean:
			$(RM) $(OBJS)
fclean:		clean
			$(RM) $(NAME)
re:			fclean all

.PHONY:		all clean fclean re
