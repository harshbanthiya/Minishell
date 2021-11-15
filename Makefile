# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:31:26 by sfournie          #+#    #+#              #
#    Updated: 2021/11/15 16:51:26 by hbanthiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC		= gcc
CFLAGS	= -Wall -Wextra -g
C_OBJS	= $(CC) $(CFLAGS) $(MINISHELL_TEST_FLAGS) $(INCS_FLAGS) -c $< -o $@
C_MAIN	= $(CC) $(CFLAGS) $(MINISHELL_TEST_FLAGS) $(INCS_FLAGS) -lcurses $(LIB_ALL)
#

# Program
NAME	= minishell
#

# Directories
DIR_SRCS	= srcs
DIR_OBJS	= objs
DIR_INCS	= includes
DIR_MAINS	= mains
DIR_BUILT	= $(DIR_SRCS)/builtin
DIR_LST		= $(DIR_SRCS)/dlist
DIR_ENV		= $(DIR_SRCS)/environment
DIR_UTIL	= $(DIR_SRCS)/utils
DIR_SH		= $(DIR_SRCS)/shell
DIR_SIG		= $(DIR_SRCS)/signal
DIR_PARSE	= $(DIR_SRCS)/parsing
DIR_SCAN	= $(DIR_SRCS)/scan
DIR_CMD		= $(DIR_SRCS)/cmd
DIR_LFT		= libft
DIR_RDLN	= $(DIR_INCS)/readline
#

# Libraries and Includes
LIB_LFT		= $(DIR_LFT)/libft.a
LIB_RDLN	= $(DIR_RDLN)/libreadline.a
LIB_HIST	= $(DIR_RDLN)/libhistory.a

LIB_ALL		= $(LIB_LFT) $(LIB_RDLN) $(LIB_HIST)
INCS_ALL	= $(DIR_LFT) $(DIR_RDLN) $(DIR_INCS)
INCS_FLAGS	= $(patsubst %,-I%,$(INCS_ALL))
#

# Makefiles
MK_LFT		= make -C $(DIR_LFT)
#

# Mains
MAIN		= $(DIR_MAINS)/minishell.c
MAIN_GEN	= $(DIR_MAINS)/main_general.c
MAIN_WILD	= $(DIR_MAINS)/main_wild.c

# Headers
HEADERS	=	ms_builtin.h dlist.h ms_environment.h \
				minishell.h ms_execution.h ms_shell.h \
				ms_parse.h ms_parsing.h ms_path.h ms_scan.h \
				ms_utils.h ms_utility.h ms_signal.h
#

# Sources and Objects
SRC	= 	environment.c variable.c variable_print.c variable_utils.c \
		memory.c \
		shell.c \
		terminal.c modes.c \
		sig_general.c \
		file.c \
		ft_merge_split.c ft_splitn.c ft_strfuse.c\
		dlist.c node.c \
		cd.c echo.c env.c exit.c export.c pwd.c unset.c \
		parse1.c parse2.c parse3.c parse_utils.c parse_utils2.c sparse.c \
		expand.c c_types.c cleanup.c \
		scan1.c scan2.c scan3.c scan4.c \
		builtin_utils.c builtin_fd_list.c \
		minishell_error_msg.c \
		cmd_exec_builtin.c cmd_exec_cmds.c cmd_exec_command.c cmd_fd_reds_utils.c \
		cmd_pipe.c cmd_prep.c cmd_prep2.c cmd_redirections.c cmd_heredoc_expander.c \
		convert_ast_cmd.c expand_string_node.c path.c string_node2string.c t_cmd_redirection.c \
		exec.c env_expander.c \
		cmd_status.c interactive_shell.c split_expanded_str.c string_utils.c 

_OBJ	= $(SRC:.c=.o)
OBJ		= $(patsubst %,$(DIR_OBJS)/%,$(_OBJ))

$(DIR_OBJS)/%.o :  %.c
		@ $(C_OBJS)

vpath %.c $(DIR_SRCS)
vpath %.c $(DIR_OBJS)
vpath %.c $(DIR_INCS)
vpath %.c $(DIR_MAINS)
vpath %.c $(DIR_BUILT)
vpath %.c $(DIR_LST)
vpath %.c $(DIR_ENV)
vpath %.c $(DIR_UTIL)
vpath %.c $(DIR_SH)
vpath %.c $(DIR_PARSE)
vpath %.c $(DIR_SIG)
vpath %.c $(DIR_SCAN)
vpath %.c $(DIR_CMD)

SRCS		= $(SRC)
OBJS		= $(OBJ)
#
all		: $(NAME)

$(NAME)	: $(DIR_INCS) $(LIB_LFT) $(SRCS) $(MAIN) $(DIR_OBJS) $(OBJS)
		@ $(C_MAIN) $(MAIN) $(OBJS) -o $(NAME)
		@ stty -echoctl
		# $(shell echo "Compiling minishell done!")
		# $(shell echo "Executable is : $(NAME)")

$(DIR_OBJS)	: 
		@ mkdir objs

wild	: $(MAIN_WILD) _wild $(NAME)
_wild	: 
		$(eval MAIN=$(MAIN_WILD))

gen	: $(MAIN_GEN) _gen $(NAME)
_gen	: 
		$(eval MAIN=$(MAIN_GEN))

$(LIB_LFT)	:
		@ $(MK_LFT) all

clean	: 
		@ rm -rf $(DIR_OBJS)
		@ $(MK_LFT) clean
		# $(shell echo "minishell cleaned!")

fclean	: clean
		@ $(MK_LFT) fclean
		@ rm -rf $(NAME)
		

re		: fclean all

bonus	: $(DIR_I) $(LFT) $(SRC) $(DIR_O) $(OBJ) $(MAIN_B)
		@ $(CC) $(CFLAGS) -I$(DIR_I)/ -I$(LFT_D)/ $(LFT) $(MAIN_B) $(OBJ) -o $(NAME)
		# $(shell echo "Compiling minishell with bonus done!")
		# $(shell echo "Executable is : $(NAME)")

.PHONY	: all re clean fclean bonus gen wild
