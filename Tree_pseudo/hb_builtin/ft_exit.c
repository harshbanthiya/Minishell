#include "../shell.h"

int     ft_exit(cmd *command)
{
    int     exit_status;

    exit_status = -1; /* -1 for failure, remember to define MACROS or have a struct to have consistent values */
    printf("Command Count: %d\n", command->argc);
    if (command->argc == 2)
    {
        exit_status = ft_atoi(command->argv[1]);
        exit(exit_status);
    }
    else 
    {
        ft_putstr_fd("exit: too many args\n", 1);
        exit_status = 1;
    }
    return (exit_status);
}
