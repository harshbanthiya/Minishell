# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:31:26 by sfournie          #+#    #+#              #
#    Updated: 2021/11/12 16:59:36 by sfournie         ###   ########.fr        #
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
DIR_TERM	= $(DIR_SRCS)/terminal
DIR_SIG		= $(DIR_SRCS)/signal
DIR_PARSE	= $(DIR_SRCS)/parsing
DIR_SCAN	= $(DIR_SRCS)/scan
DIR_INTER	= $(DIR_SRCS)/interpret
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
MAIN_ENV	= $(DIR_MAINS)/main_env.c
MAIN_PARSE	= $(DIR_MAINS)/main_parse.c
MAIN_TERM	= $(DIR_MAINS)/main_term.c
MAIN_SIG	= $(DIR_MAINS)/main_signal.c
MAIN_TREE	= $(DIR_MAINS)/main_tree.c
MAIN_WILD	= $(DIR_MAINS)/main_wild.c

# Headers
_HEADERS	=	builtin.h dlist.h environment.h \
				minishell.h parsing.h shell.h \
				signal.h utility.h
HEADERS		= $(patsubst %,ms_%,$(_HEADERS))
#

# Sources and Objects
SRC	= 	environment.c variable.c variable_print.c variable_utils.c\
		memory.c \
		shell.c \
		terminal.c modes.c \
		sig_general.c \
		file.c \
		ft_merge_split.c ft_splitn.c ft_strfuse.c\
		dlist.c node.c \
		cd.c echo.c env.c exit.c export.c pwd.c unset.c \
		expand.c parse.c c_types.c cleanup.c\
		builtin_utils.c \
		interpret_utils.c interpret_tree.c \
		parse_tree.c parse_utils.c scan_utils.c token_list.c \
		cmd_execute.c cmd.c handle_quotes.c cmd_utils.c \
		replace_env.c replace_env_utils.c cmd_status.c interactive_shell.c

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
vpath %.c $(DIR_TERM)
vpath %.c $(DIR_PARSE)
vpath %.c $(DIR_SIG)
vpath %.c $(DIR_INTER)
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

parse	: $(MAIN_PARSE) _parse $(NAME)
_parse	: 
		$(eval MAIN=$(MAIN_PARSE))
		
term	: $(MAIN_TERM) _term $(NAME)
_term	:
		$(eval MAIN=$(MAIN_TERM))

signal	: $(MAIN_SIG) _sig $(NAME)
_sig	: 
		$(eval MAIN=$(MAIN_SIG))

tree	: $(MAIN_TREE) _tree $(NAME)
_tree	: 
		$(eval MAIN=$(MAIN_TREE))


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

.PHONY	: all re clean fclean bonus parse term tree signal wild
