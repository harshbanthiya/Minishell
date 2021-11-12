/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/08 16:08:08 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	handle_input(char *str, int fd)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "export", 6))
		ft_export(str + 7, get_env());
	else if (!ft_strncmp(str, "unset", 5))
		ft_unset(str + 6, get_env());
	else if (!ft_strncmp(str, "echo", 4))
		ft_echo(str + 5, 1);
	else if (!ft_strncmp(str, "env", 3))
		ft_env(1);
	return (1);
}

int	main(int argn, char **argv, char **envp)
{
	char	*user_in;

	// envp[0] = NULL;
	init_shell(envp);
	user_in = readline("prompt : ");
	while (user_in != NULL && *user_in)
	{
		add_history(user_in);
		handle_input(user_in, 1);
		ft_free(user_in);
		user_in = readline("prompt : ");
	}
	ft_free(user_in);
	// free_shell(get_shell());
}