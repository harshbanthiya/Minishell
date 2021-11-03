NAME			=	minishell
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
LEAKS			=	-g -fsanitize=address -fsanitize=undefined -std=c99
RM				=	rm -f

INCLUDES_PATH	=	./includes/

GNL				=	libgnl.a
GNLS			=	-L./libs/gnl -lgnl
FT				=	libft.a
FTS				=	-L./libs/libft -lft
INCS			=	-I$(INCLUDES_PATH)
SRC_PATH		=	./srcs/
SRC_FILE		=	main.c readline.c \
					scanner/set_token_list.c scanner/gen_token_string.c \
					util.c scanner/replace_env.c scanner/strip_quotes.c \
					scanner/util_replace_env1.c scanner/util_replace_env2.c \
					execute/execute.c execute/exec_cd.c execute/exec_echo.c \
					execute/exec_env.c execute/exec_exit.c \
					execute/exec_export.c execute/exec_pwd.c \
					execute/exec_unset.c \
					envp/envp.c envp/sort_env.c envp/unset_env_one.c \
					interpret_tree/execute_pipe.c \
					interpret_tree/execute_tree.c \
					command/command_prepare.c command/command.c command/command_path.c\
					parse/node.c parse/parse_command.c parse/parse_top.c \
					parse/term.c

SRCS			=	$(SRC_FILE:%.c=$(SRC_PATH)%.c)
OBJS			=	$(SRCS:.c=.o)

all:				$(NAME)
$(NAME):			$(GNL) $(FT)
					$(CC) $(CFLAGS) $(INCS) $(SRCS) $(GNLS) $(FTS) \
							-o $(NAME)
$(GNL):
					$(MAKE) -C ./libs/gnl/
$(FT):
					$(MAKE) bonus -C ./libs/libft/

debug:				fclean $(GNL) $(FT)
					$(CC) $(CFLAGS) $(LEAKS) $(INCS) $(GNLS) $(FTS) $(SRCS) \
							-o $(NAME)
clean:
					$(MAKE) -C ./libs/gnl clean
					$(MAKE) -C ./libs/libft clean
					$(RM) $(OBJS)

fclean:				clean
					$(RM) ./libs/gnl/$(GNL)
					$(RM) ./libs/libft/$(FT)
					$(RM) $(NAME)
re:					fclean all

.PHONY:				all debug clean fclean re
