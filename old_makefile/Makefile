NAME = minishell
CC = gcc
CFLAGS := -Werror -Wall -Wextra -g -Iincludes/readline
CFLAGS += -fsanitize=address
LINK_LIB := -lreadline -lcurses
LIBFT_PATH = libft
LIBFT_MAKE = $(MAKE) -C $(LIBFT_PATH)
LIBFT_LIB = -L./libft -lft

LDFLAGS = $(LIBFT_LIB) $(LINK_LIB)

HEADER_FILES = includes/ms_builtin.h includes/ms_environment.h includes/ms_scan.h includes/ms_parse.h	\
	includes/ms_execution.h includes/minishell.h includes/ms_path.h includes/ms_utils.h includes/ms_utility.h \
	includes/ms_signal.h includes/ms_shell.h includes/ms_parsing.h includes/dlist.h

SRCS = srcs/cmd/cmd_exec_builtin.c srcs/cmd/cmd_exec_cmds.c srcs/cmd/cmd_exec_command.c		\
	srcs/cmd/cmd_fd_reds_utils.c srcs/cmd/cmd_pipe.c srcs/cmd/cmd_redirections.c srcs/cmd/cmd_heredoc_expander.c	\
	srcs/cmd/cmd_prep.c	srcs/cmd/cmd_prep2.c srcs/cmd/convert_ast_cmd.c	\
	srcs/cmd/expand_string_node.c srcs/cmd/path.c srcs/cmd/string_node2string.c srcs/cmd/exec.c	\
	srcs/cmd/t_cmd_redirection.c														\
																			\
	srcs/dlist/dlist.c srcs/dlist/node.c									\
																			\
	srcs/environment/env_expander.c srcs/environment/environment.c			\
	srcs/environment/variable_print.c srcs/environment/variable_utils.c srcs/environment/variable.c \
																			\
	srcs/parsing/c_types.c srcs/parsing/cleanup.c srcs/parsing/expand.c srcs/parsing/parse_utils.c \
	srcs/parsing/parse1.c srcs/parsing/parse2.c srcs/parsing/parse3.c srcs/parsing/parse_utils2.c	\
	srcs/parsing/sparse.c srcs/scan/scan1.c srcs/scan/scan2.c	srcs/scan/scan3.c	srcs/scan/scan4.c \
	srcs/scan/utils.c srcs/shell/cmd_status.c srcs/shell/interactive_shell.c 	\
	srcs/shell/minishell_error_msg.c srcs/shell/modes.c srcs/shell/shell.c srcs/shell/terminal.c\
																			\
	srcs/builtin/builtin_utils.c srcs/builtin/builtin_fd_list.c srcs/builtin/echo.c \
	srcs/builtin/env.c srcs/builtin/exit.c	\
	srcs/builtin/cd.c 	\
	srcs/builtin/export.c srcs/builtin/pwd.c srcs/builtin/unset.c		\
																			\
	srcs/signal/sig_general.c srcs/utils/file.c srcs/utils/ft_merge_split.c \
	srcs/utils/ft_splitn.c srcs/utils/ft_strfuse.c srcs/utils/memory.c srcs/utils/split_expanded_str.c \
	srcs/utils/string_utils.c mains/minishell.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(OBJS): $(HEADER_FILES)

$(NAME): ${HEADER_FILES} ${OBJS}
	$(LIBFT_MAKE)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)  $(LDFLAGS)

clean:
	$(LIBFT_MAKE) clean
	${RM} ${OBJS}

fclean: clean
	$(LIBFT_MAKE) fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
