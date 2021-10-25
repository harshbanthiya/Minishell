#include "../shell.h"

int     exec_echo_no_arg(void)
{
    ft_putstr_fd("\n", 1);
    return (1);
}

int     exec_echo_only_n(void)
{
    ft_putstr_fd("", 1);
    return (1);
}

int     ft_echo(t_cmd  *command)
{
    int     index;
    int     n_tag;
    int     exit_status;

    n_tag = false;
    index = 1;
    if (command->argc == 1)
    {
        exit_status = exec_echo_no_arg();
        return (exit_status);
    }    
    if (ft_strncmp(command->argv[index], "-n", 3) == 0)
    {
        if (command->argc == 2)
        {
            exit_status = exec_echo_only_n();
            return (exit_status);
        }
        n_tag = true;
        index++;
    }
    while (index < command->argc)
    {
        ft_putstr_fd(command->argv[index], 1);
        if ((index + 1) < command->argc)
            ft_putstr_fd(" ", 1);
        index++;
    }
    if (!n_tag)
        ft_putstr_fd("\n", 1);
    exit_status = 1; /* 1 is success message, make a struct or define macros of all the errors */ 
    return (exit_status);
}