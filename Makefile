# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:31:26 by sfournie          #+#    #+#              #
#    Updated: 2021/10/08 16:54:38 by sfournie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC		= gcc
CFLAGS	= -Wall -Wextra -g
C_OBJ	= $(CC) $(CFLAGS)  -I$(DIR_INCS)/ -I$(LFT_D)/ -c $< -o $@
C_MAIN	= $(CC) $(CFLAGS) -lreadline -I$(DIR_INCS)/ -I$(LFT_D)/ $(LFT) $(MAIN) $(OBJS) -o $(NAME)
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
#

# Mains
MAIN		= $(DIR_MAINS)/main_general.c
MAIN_ENV	= $(DIR_MAINS)/main_env.c

# General files
_SRC_GEN	= environment.c variable.c\
			list.c \
			memory.c \
			shell.c \
			terminal.c get_terminal.c set_terminal.c
SRC_GEN		= $(patsubst %,$(DIR_SRCS)/%,$(_SRC_GEN))

_OBJ_GEN	= $(_SRC_GEN:.c=.o)
OBJ_GEN		= $(patsubst %,$(DIR_OBJS)/%,$(_OBJ_GEN))

$(DIR_OBJS)/%.o :  $(DIR_SRCS)/%.c
		@ $(C_OBJ)
#

# Builtin files
_SRC_BUILT	= cd.c echo.c env.c exit.c export.c pwd.c unset.c \
			builtin_utils.c
SRC_BUILT	= $(patsubst %,$(DIR_BUILT)/%,$(_SRC_BUILT))

_OBJ_BUILT	= $(_SRC_BUILT:.c=.o)
OBJ_BUILT	= $(patsubst %,$(DIR_OBJS)/%,$(_OBJ_BUILT))

$(DIR_OBJS)/%.o :	$(DIR_BUILT)/%.c
		@ $(C_OBJ)
#

# All files
SRCS		= $(SRC_GEN) $(SRC_BUILT)
OBJS		= $(OBJ_BUILT) $(OBJ_GEN) 
#

all		: $(NAME)

$(NAME)	: $(DIR_INCS) $(LFT) $(SRCS) $(MAIN) $(DIR_OBJS) $(OBJS)
		@ $(C_MAIN)
		# $(shell echo "Compiling minishell done!")
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
		# $(shell echo "Compiling pipex with bonus done!")
		# $(shell echo "Executable is : $(NAME)")

.PHONY	: all re clean fclean bonus
