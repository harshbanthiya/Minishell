#include "../shell.h"

int     ft_pwd(cmd *command)
{
    char    working_dir[1024];

    if (getcwd(working_dir, sizeof(working_dir)) != NULL)
    {
        ft_putstr_fd(working_dir, 1);
        ft_putstr_fd("\n", 1);
    }
    else 
        ft_putstr_fd(strerror(errno) , 1);
    global_exit_code = 0;
    return (1);
}