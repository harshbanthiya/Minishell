/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/28 17:35:30 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	handle_input(char *str)
{
	char **split;

	str = parse_cmdline(str);
	split = ft_split(str, ' ');
	if (split != NULL)
	{
		if (is_builtin(split[0]))
			run_builtin(split[0], &split[1]);
	}
	ft_free(str);
	free_split(split);
	return (0);
}

int	main(int argn, char **argv, char **envp)
{
	char	*user_in;

	// envp[0] = NULL;
	argn = 0;
	argv = NULL;
	init_shell(envp);
	init_signals();
	user_in = readline("prompt : ");
	while (user_in != NULL && *user_in)
	{
		add_history(user_in);
		handle_input(user_in);
		ft_free(user_in);
		user_in = readline("prompt : ");
	}
	ft_free(user_in);
	free_shell();
}