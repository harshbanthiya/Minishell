LIBFT_PATH = ../libft
LIBFT_MAKE = $(MAKE) -C $(LIBFT_PATH)
LIBFT_LIB = ../libft/libft.a
LDFLAGS = -lreadline

SRCS_PARSE = $(wildcard ../srcs/scan/scan*.c ../srcs/parsing/parse*.c) ../libft/ft_memcpy.c

parse_test: Makefile parse_test.c test.c test.h $(SRCS_PARSE) ../includes/ms_parse.h
	$(LIBFT_MAKE)
	gcc -Werror -Wall -Wextra -g -o $@ parse_test.c test.c $(SRCS_PARSE) ${LIBFT_LIB}