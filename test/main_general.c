/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/08 18:07:06 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	handle_input(char *str, int fd)
{
	/* to simulate having a token as cmd name */
	char **split;

	split = ft_split(str, ' ');
	if (split == NULL)
		return (0);
	/* end simulate */
	if (is_builtin(split[0]))
		run_builtin(str);
	free_split(split);
	return (0);
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