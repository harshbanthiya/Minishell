LIBFT_PATH = ../libft
LIBFT_MAKE = $(MAKE) -C $(LIBFT_PATH)
LIBFT_LIB = ../libft/libft.a
LDFLAGS = -lreadline -lcurses
SRCS = ../srcs/cmd/cmd_prep.c ../srcs/cmd/cmd_prep2.c ../srcs/cmd/cmd_exec_command.c	\
	../srcs/cmd/cmd_exec_cmds.c ../srcs/cmd/cmd_pipe.c ../srcs/cmd/cmd_redirections.c ../srcs/cmd/cmd_heredoc_funcs.c	\
	../srcs/cmd/convert_ast_cmd.c												\
	../srcs/shell/cmd_status.c ../srcs/signal/signal.c ../srcs/shell/minishell_error_msg.c ../srcs/cmd/exec.c	\
	../srcs/cmd/cmd_exec_builtin.c														\
																			\
	../srcs/cmd/t_cmd_redirection.c ../srcs/cmd/cmd_fd_reds_utils.c								\
																			\
	../srcs/dlist/dlist.c ../srcs/dlist/node.c																		\
	../srcs/scan/scan1.c ../srcs/scan/scan2.c ../srcs/scan/scan3.c ../srcs/scan/scan4.c ../srcs/parsing/parse1.c ../srcs/parsing/parse2.c ../srcs/parsing/parse3.c			\
	../srcs/parsing/parse_utils.c ../srcs/parsing/parse_utils2.c											\
	../srcs/environment/environment.c ../srcs/environment/variable_print.c ../srcs/environment/variable_utils.c ../srcs/environment/variable.c		\
	../srcs/cmd/path.c ../srcs/cmd/string_node2string.c ../srcs/environment/env_expander.c ../srcs/cmd/cmd_heredoc_expander.c	\
	../srcs/cmd/expand_string_node.c ../srcs/utils/split_expanded_str.c 			\
	../srcs/shell/interactive_shell.c ../srcs/shell/modes.c ../srcs/shell/shell.c ../srcs/shell/terminal.c	\
	../srcs/builtin/builtin_utils.c  ../srcs/builtin/builtin_fd_list.c ../srcs/builtin/echo.c ../srcs/builtin/env.c ../srcs/builtin/exit.c \
	../srcs/builtin/cd.c ../srcs/builtin/cd.c 	\
	../srcs/builtin/export.c ../srcs/builtin/pwd.c ../srcs/builtin/unset.c		\
	../srcs/utils/ft_merge_split.c ../srcs/utils/ft_splitn.c ../srcs/utils/ft_strfuse.c ../srcs/utils/memory.c	\
	../srcs/utils/string_utils.c


HEADERS = ../includes/ms_environment.h \
		  ../includes/ms_parse.h \
		  ../includes/ms_execution.h ../includes/readline/readline.h ../includes/readline/history.h \
		  ../includes/minishell.h

TEST_UTILS = test.c \
			 test.h

VALGRIND = valgrind -q --leak-check=full --errors-for-leak-kinds=all --show-leak-kinds=all --error-exitcode=99

run: parse_test path_test exec_test command_exec_test ast2cmdinvo_test
	${VALGRIND} ./parse_test
	${VALGRIND} ./exec_test
	${VALGRIND} ./command_exec_test
	${VALGRIND} ./ast2cmdinvo_test


parse_test: Makefile parse_test.c test.c test.h $(SRCS) ../includes/ms_parse.h
	$(LIBFT_MAKE)
	gcc -Werror -Wall -Wextra -g -o $@ parse_test.c test.c $(SRCS) ${LIBFT_LIB} $(LDFLAGS)


exec_test: exec_test.c ${TEST_UTILS} ${SRCS} ${HEADERS}
	$(LIBFT_MAKE)
	gcc -Werror -Wall -Wextra -g -o $@ $^ ${LIBFT_LIB} $(LDFLAGS)

command_exec_test: command_exec_test.c ${TEST_UTILS} ${SRCS} ${HEADERS}
	$(LIBFT_MAKE)
	gcc -Werror -Wall -Wextra -g -o $@ $^ ${LIBFT_LIB} $(LDFLAGS)

ast2cmdinvo_test: ast2cmdinvo_test.c ${TEST_UTILS} ${SRCS} ${HEADERS}
	$(LIBFT_MAKE)
	gcc -Werror -Wall -Wextra -g -o $@ $^ ${LIBFT_LIB} $(LDFLAGS)


fclean:
	rm -f ./parse_test
	rm -f ./path_test
	rm -f ./exec_test
	rm -f ./command_exec_test
	rm -f ./ast2cmdinvo_test

re: fclean run
