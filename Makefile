# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:31:26 by sfournie          #+#    #+#              #
#    Updated: 2021/11/01 14:26:25 by sfournie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC		= gcc
CFLAGS	= -Wall -Wextra -g
C_OBJS	= $(CC) $(CFLAGS) $(INCS_FLAGS) -c $< -o $@
C_MAIN	= $(CC) $(CFLAGS) $(INCS_FLAGS) -lcurses $(LIB_ALL)
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
DIR_LST		= $(DIR_SRCS)/list
DIR_ENV		= $(DIR_SRCS)/environment
DIR_UTIL	= $(DIR_SRCS)/utils
DIR_SH		= $(DIR_SRCS)/shell
DIR_TERM	= $(DIR_SRCS)/terminal
DIR_SIG		= $(DIR_SRCS)/signal
DIR_PARSE	= $(DIR_SRCS)/parsing
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
MAIN		= $(DIR_MAINS)/main_general.c
MAIN_ENV	= $(DIR_MAINS)/main_env.c
MAIN_PARSE	= $(DIR_MAINS)/main_parse.c
MAIN_TERM	= $(DIR_MAINS)/main_term.c
MAIN_SIG	= $(DIR_MAINS)/main_signal.c

# Sources and Objects
SRC	= 	environment.c variable.c variable_print.c\
		memory.c \
		shell.c \
		terminal.c modes.c \
		sig_general.c \
		file.c \
		merge_split.c splitn.c ft_strfuse.c\
		list.c node.c \
		cd.c echo.c env.c exit.c export.c pwd.c unset.c \
		expand.c parse.c c_types.c cleanup.c\
		builtin_utils.c

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

parse	: $(MAIN_PARSE) _parse $(NAME)
_parse	: 
		$(eval MAIN=$(MAIN_PARSE))
		
term	: $(MAIN_TERM) _term $(NAME)
_term	:
		$(eval MAIN=$(MAIN_TERM))

signal	: $(MAIN_SIG) _sig $(NAME)
_sig	: 
		$(eval MAIN=$(MAIN_SIG))


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

.PHONY	: all re clean fclean bonus parse term
