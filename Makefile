# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:31:26 by sfournie          #+#    #+#              #
#    Updated: 2021/10/24 18:47:48 by sfournie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC		= gcc
CFLAGS	= -Wall -Wextra -g
C_OBJ	= $(CC) $(CFLAGS)  -I$(DIR_INCS)/ -I$(LFT_D)/ -c $< -o $@
C_MAIN	= $(CC) $(CFLAGS) -lreadline -I$(DIR_INCS)/ -I$(LFT_D)/ \
		$(LFT)
#

# Program
NAME	= minishell
#

# Libft
_LFT	= libft.a
LFT_D	= libft
LFT		= $(LFT_D)/$(_LFT)
LFT_M	= cd $(LFT_D) && make
#

# Directories
DIR_SRCS	= srcs
DIR_OBJS	= objs
DIR_INCS	= includes
DIR_MAINS	= test
DIR_BUILT	= $(DIR_SRCS)/builtin
DIR_LST		= $(DIR_SRCS)/list
DIR_ENV		= $(DIR_SRCS)/environment
DIR_UTIL	= $(DIR_SRCS)/utils
DIR_SH		= $(DIR_SRCS)/shell
DIR_TERM	= $(DIR_SRCS)/terminal
DIR_PARSE	= $(DIR_SRCS)/parsing
#

# Mains
MAIN		= $(DIR_MAINS)/main_general.c
MAIN_ENV	= $(DIR_MAINS)/main_env.c
MAIN_PARSE	= $(DIR_MAINS)/main_parse.c
MAIN_TERM	= $(DIR_MAINS)/main_term.c

# General files
SRC	= 	environment.c variable.c variable_print.c\
		memory.c \
		shell.c modes.c \
		terminal.c signal.c \
		file.c \
		merge_split.c splitn.c ft_string.c\
		list.c node.c \
		cd.c echo.c env.c exit.c export.c pwd.c unset.c \
		expand.c parse.c c_types.c cleanup.c\
		builtin_utils.c

_OBJ	= $(SRC:.c=.o)
OBJ		= $(patsubst %,$(DIR_OBJS)/%,$(_OBJ))
#

$(DIR_OBJS)/%.o :  %.c
		@ $(C_OBJ)

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

# All files
SRCS		= $(SRC)
OBJS		= $(OBJ)
#

all		: $(NAME)

$(NAME)	: $(DIR_INCS) $(LFT) $(SRCS) $(MAIN) $(DIR_OBJS) $(OBJS)
		@ $(C_MAIN) $(MAIN) $(OBJS) -o $(NAME)
		# $(shell echo "Compiling minishell done!")
		# $(shell echo "Executable is : $(NAME)")

parse	: $(DIR_INCS) $(LFT) $(SRCS) $(MAIN) $(DIR_OBJS) $(OBJS)
		@ $(C_MAIN) $(MAIN_PARSE) $(OBJS) -o $(NAME)
		# $(shell echo "Compiling minishell for parsing tests done!")
		# $(shell echo "Executable is : $(NAME)")

term	: $(DIR_INCS) $(LFT) $(SRCS) $(MAIN) $(DIR_OBJS) $(OBJS)
		@ $(C_MAIN) $(MAIN_TERM) $(OBJS) -o $(NAME)
		# $(shell echo "Compiling minishell for parsing tests done!")
		# $(shell echo "Executable is : $(NAME)")

$(LFT)	:
		@ $(LFT_M) all

clean	: 
		@ rm -rf $(OBJS)
		@ $(LFT_M) clean
		# $(shell echo "minishell cleaned!")

fclean	: clean
		@ $(LFT_M) fclean
		@ rm -rf $(NAME)
		

re		: fclean all

bonus	: $(DIR_I) $(LFT) $(SRC) $(DIR_O) $(OBJ) $(MAIN_B)
		@ $(CC) $(CFLAGS) -I$(DIR_I)/ -I$(LFT_D)/ $(LFT) $(MAIN_B) $(OBJ) -o $(NAME)
		# $(shell echo "Compiling minishell with bonus done!")
		# $(shell echo "Executable is : $(NAME)")

.PHONY	: all re clean fclean bonus parse term
