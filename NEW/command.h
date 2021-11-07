#ifndef COMMAND_H
#define COMMAND_H
#include <unistd.h>
#include <stdbool.h>
#include "Tree.h"

struct  cmd
{
    int     argc;
    char    **argv;
    bool    stdin_pipe;
    bool    stdout_pipe;
    int     pipe_read;
    int     pipe_write;
    char    *redirect_in;
    char    *redirect_out;
    bool    async;
};

typedef struct cmd t_cmd;

void     ignore_signal_for_shell(void);
void     set_prompt(char *str);
char     *get_prompt(void);

#endif