#include "parse.h"

int     isBuiltin(parse_info *cmd)
{
    char        *program;

    program = cmd->tokens[0];
    if (strcmp(program, "cd") == 0)
        return (0);
    else if (strcmp(program, "exit") == 0)
        return (1);
    return (-1);
}

int     executeBuiltin(parse_info *cmd)
{
    if (strcmp(cmd->tokens[0], "cd") == 0)
    {
        if (chdir(cmd->tokens[1]) != -1)
            return (0);
        else 
            strerror(errno);
    }
    else if (strcmp(cmd->tokens[0], "exit") == 0)
        exit(0);
    return (1);
}

void make_prompt(char *prompt_buff, char *origPrompt)
{
    char    *cwd;

    cwd = getcwd(cwd, 150);
    strcpy(prompt_buff, origPrompt);
    strcat(prompt_buff, cwd);
    strcat(prompt_buff, ": ");
    free(cwd);
}

char   *read_cl(char *command_line_buffer)
{
    /* If the buffer has already  been allocated, return Memory to the pool */
    if (command_line_buffer)
    {
        free(command_line_buffer);
        command_line_buffer = (char *) NULL;
    }
    /* Get the line */
    command_line_buffer = readline("$ ");
    /* If the line has text save it to history */
    if (command_line_buffer && *command_line_buffer)
        add_history(command_line_buffer);
    return (command_line_buffer);
}

int     executeCommand(parse_info *cmd)
{
    char        **cmd_args;
    int         i;

    i = 0;
    cmd_args = malloc(cmd->numArgs + 2 * sizeof(char *));
    while (i <= cmd->numArgs)
    {
        cmd_args[i] = cmd->tokens[i];
        i++;
    }    
    cmd_args[cmd->numArgs + 1] = NULL;
    if (execvp(cmd_args[0], cmd_args) == -1)
        strerror(errno);
    free(cmd_args);
    return (0);
}

int main(int argc, char **argv)
{
    char        *prompt;
    char        *orig_prompt;        /* We will need to rebuild the pwd bit each time */
    parse_info  *info;
    char        *cmdline;
    int         is_builtin;
    pid_t       wpid;
    pid_t       child;
    int         status;
    
    
    prompt = malloc(sizeof(char) * 10);
    info = malloc(sizeof(parse_info));
    strcpy(prompt, "msh: ");
    orig_prompt = strdup(prompt);
    init_info(info);
    is_builtin = 0;
    rl_bind_key('\t', rl_complete);
    while(1)
    {
        make_prompt(prompt, orig_prompt);
        cmdline = NULL;
        read_cl(cmdline);
        if (strcmp(cmdline, "") == 0)     /* Skip empty lines */
            continue ;
        info = parse(cmdline);
        free(cmdline);
        is_builtin = isBuiltin(info);
        if (is_builtin != -1)
            executeBuiltin(info);
        else 
        {
            /* Executing a real command */
            child = fork();
            if (child == 0)
            {
                executeCommand(info);
                exit(0);
            }
            else 
            {
                wpid = waitpid(child, &status, WUNTRACED);
                while (!WIFEXITED(status) && !WIFSIGNALED(status))
                    wpid = waitpid(child, &status, WUNTRACED);
            }
        }
    }
    free_info(info);
    free(orig_prompt);
    free(prompt);
}