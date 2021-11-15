/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 10:02:02 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	handle_input(char *str)
{
	t_cmd	cmd;

	str = parse_cmdline(str);
	cmd.argv = ft_split(str, ' ');
	if (cmd.argv != NULL)
	{
		if (is_builtin(cmd.argv[0]))
			run_builtin(cmd.argv, get_env(), 0);
	}
	ft_free(str);
	free_split(cmd.argv);
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
	print_welcome();
	user_in = ft_readline();
	while (user_in != NULL && *user_in)
	{
		add_history(user_in);
		handle_input(user_in);
		ft_free(user_in);
		user_in = ft_readline();
	}
	ft_free(user_in);
	free_shell();
}