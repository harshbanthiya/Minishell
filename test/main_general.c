/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/18 17:05:19 by sfournie         ###   ########.fr       */
=======
/*   Updated: 2021/10/24 16:00:02 by sfournie         ###   ########.fr       */
>>>>>>> develop
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
	signal(SIGQUIT, sig_quit);
	signal(EOF, sig_eof);
	signal(SIGINT, sig_intr);
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