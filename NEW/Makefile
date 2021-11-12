CC = gcc
CFLAGS = -g 

default: minishell

minishell: scanner.o minishell.o command.o
	$(CC) $(CFLAGS) scanner.o minishell.o command.o -o minishell

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c
	
minishell.o: minishell.c
	$(CC) $(CFLAGS) -c minishell.c
	
#execute.o: execute.c execute.h
#$(CC) $(CFLAGS) -c execute.c
	
#parser.o: parser.c parser.h
#$(CC) $(CFLAGS) -c parser.c

scanner.o: scanner.h scanner.c
	$(CC) $(CFLAGS) -c scanner.c 
	
#tree.o: tree.c tree.h
#$(CC) $(CFLAGS) -c tree.c 

clean: 
	rm *.o