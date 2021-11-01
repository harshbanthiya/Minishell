/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/28 17:26:55 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/* mode 0 : non-interactive, mode 1 : interactive */


static int	handle_input(char *str)
{

	// if (!name || !is_builtin(name))
	// 	return (0);
	if (!ft_strcmp(str, "0"))
		sh_change_mode(0);
	else if (!ft_strcmp(str, "1"))
		sh_change_mode(1);
	return (1);
}

int	main(int argn, char **argv, char **envp)
{
	char		*user_in;

	argn = 0;
	argv = NULL;
	init_signals();
	init_shell(envp);
	sh_change_mode(1);
	user_in = readline("prompt : ");
	while (user_in != NULL)
	{
		sh_change_mode(1);
		add_history(user_in);
		handle_input(user_in);
		free(user_in);
		user_in = readline("prompt : ");
	}
	free(user_in);
	exit_shell();
	return (0);
}