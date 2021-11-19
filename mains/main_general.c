/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/18 15:41:26 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	handle_input(char *str)
{
	char	**split;

	str = parse_cmdline(str);
	split = ft_split(str, ' ');
	if (split != NULL)
	{
		if (!ft_strcmp(split[0], "0"))
		{
			sh_change_mode(get_shell(), 0);
		}
		else if (!ft_strcmp(split[0], "1"))
		{
			sh_change_mode(get_shell(), 1);
		}
		else if (is_builtin(split[0]))
		{
			set_status(run_builtin(split, get_env(), 0));
		}
	}
	ft_free(str);
	free_split(split);
	return (0);
}

int	main(int argn, char **argv, char **envp)
{
	char	*user_in;

	argn = 0;
	argv = NULL;
	sh_init(envp);
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
