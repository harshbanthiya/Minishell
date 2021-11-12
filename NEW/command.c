#include "command.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <pwd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

char    *prompt = NULL;
bool    signalset = false;
void    (*SIGINT_handler)(int);

void     ignore_signal_for_shell(void)
{   
    signalset = true;
    // ignore "ctrl + c"
    SIGINT_handler = signal(SIGINT, SIG_IGN);
    // ignore "ctrl + z"
    signal(SIGTSTP, SIG_IGN);
    // ignore "ctrl + \"
    signal(SIGQUIT, SIG_IGN);
}

void    set_prompt(char *str)
{
    if (prompt != NULL)
        free(prompt);
    prompt = malloc(strlen(str) + 1);
    strcpy(prompt, str);
}

char    *get_prompt(void)
{
    return (prompt);
}