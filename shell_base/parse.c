#include "parse.h"

/* Syntax to parse: myshell command1 [< infile] [| command]* [> outfile] [&] */
#define   TOKEN_DELIMITER_STR " \t\r\n\a$"

int             is_it_in_charset(char c, char *charset)
{
        int             i;

        i = 0;
        while (charset[i] != '\0')
        {
                if (c == charset[i])
                        return (1);
                i++;
        }
        return (0);
}

void    init_info(parse_info *p)
{   
    int         i;
    //printf("init_info: initializing parse_info\n");
    write(1, "init", 4);
    write(1, "\n", 1);
    i = 0;
    p->background = FALSE;
    p->inpipefile = NULL;
    p->outpipefile = NULL;
    p->tokens = malloc(sizeof(char *) * 2);
}

parse_info  *parse(char *cmdline)
{
    parse_info      *result;
    int             cmd_pos;
    int             i;
    int             spaces;
    char            cmd_dup[(int)strlen(cmdline)];
    char            *token;

    cmd_pos = 0;
    spaces = 0;
    i = 0;
    result = malloc(sizeof(parse_info));
    /* Count the number of delimiters/separators for knowing the number of tokens */
    while (cmdline[i] != '\0')
    {
        if (is_it_in_charset(cmdline[i], TOKEN_DELIMITER_STR))
            spaces++;
    }
    result->numArgs = spaces;
    init_info(result);
    result->tokens = malloc(sizeof(char *) * result->numArgs);
    strcpy(cmd_dup, cmdline);
    token = strtok(cmd_dup, TOKEN_DELIMITER_STR);
    i = 0;
    while(token)
    {
        result->tokens[i] = malloc(strlen(token) * sizeof(char));
        strcpy(result->tokens[i++], token);
        if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, TOKEN_DELIMITER_STR);
            result->inpipefile = malloc(strlen(token) * sizeof(char));
            result->tokens[i] = malloc(strlen(token) * sizeof (char));
            strcpy(result->tokens[i++], token);
            strcpy(result->inpipefile, token);
        }
        if (strcmp(token, ">") == 0)
        {
            token = strtok(NULL, TOKEN_DELIMITER_STR);
            result->outpipefile = malloc(strlen(token) * sizeof(char));
            result->tokens[i] = malloc(strlen(token) * sizeof (char));
            strcpy(result->tokens[i++], token);
            strcpy(result->outpipefile, token);
        }
        token = strtok(NULL, TOKEN_DELIMITER_STR);
    }
    return (result);
}

void    print_info(parse_info *info)
{
    int     i;
    int     arg_n;
    
    printf("print_info: printing info about parseInfo struct\n");
    printf("Program name: %s\n", info->tokens[0]);
    i = 1;
    arg_n = 1;
    while (i <= info->numArgs)
    {
        if (strcmp(info->tokens[i], ">") != 0 && strcmp(info->tokens[i], "<")  != 0)
            printf("Arg: %d: %s\n", arg_n++, info->tokens[i]);
        i++;
    }
    if (info->inpipefile != NULL)
        printf("inpipe: %s\n", info->inpipefile);
    else 
        printf("No inpipe\n");
    if (info->outpipefile != NULL)
        printf("Outpipe: %s\n", info->outpipefile);
    else 
        printf("No outpipe\n");
    if (info->background)
        printf("This command is in background\n");
    else
        printf("This command is not in background\n"); 
}   

void    free_info(parse_info *info)
{
    printf("free_info: freeing memory associated to parseInfo struct\n");
    free(info);
}