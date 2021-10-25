NAME			=	minishell
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
SRCS			=	main.c env/env_list.c \
					#hb_builtin/ft_echo.c hb_builtin/ft_exit.c hb_builtin/ft_pwd.c \
					#Interpret/interpret_utils.c Interpret/interpret_tree.c \
					#parse/parse_tree.c parse/parse_utils.c scan/scan_utils.c scan/token_list.c \
					#cmd/cmd_execute.c cmd/cmd.c cmd/handle_quotes.c
OBJS			=	$(SRCS:.c=.o)
LIB				=	libft.a
LIBS			=	-L./libft -lft
RM				=	rm -f


all:				$(NAME)
$(NAME):			$(LIB)
					$(CC) $(CFLAGS) $(INCS) $(SRCS) $(LIBS) -o $(NAME)
$(LIB):
					$(MAKE) -C libft/
clean:
					$(MAKE) -C libft clean
					$(RM) $(OBJS)

fclean:				clean
					$(RM) libft/$(LIB)
					$(RM) $(NAME)
re:					fclean all

.PHONY:				all debug clean fclean re