#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "scanner.h"
//#include "parser.h"
//#include "execute.h"
#include "command.h"

int main()
{
   // t_tree_node     *exec_tree;
    t_token_list    token_buff;
    int             again;
    char            *line;
    size_t          len;

    ignore_signal_for_shell(); // ignore ctrl-\ ctrl-c ctrl-z 
    set_prompt("minishell : "); // set prompt
    while (1)
    {   
        again = 1;
        while (again)
        {
            again = 0;
			printf("%s", get_prompt());
			line = NULL;
			len = 0;
			ssize_t nread = getline(&line, &len, stdin);
			if (nread <= 0 && errno == EINTR) {
				again = 1;        	// signal interruption, read again
				clearerr(stdin);	// clear the error
			}
        }
        if (feof(stdin)) // user pressed ctrl-d
        {
            exit(0);
            return (0);
        }
        build_token_list(line, strlen(line), &token_buff); 
        free(line);
    }
}