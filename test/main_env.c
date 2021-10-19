/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/12 17:05:54 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	main(void)
{
	char	*user_in;
	t_list	**env;

	init_shell(NULL);
	user_in = readline("export NAME=value : ");
	while (user_in != NULL && *user_in)
	{
		env = get_env();
		ft_export(user_in, env);
		ft_env(1);
		user_in = readline("export NAME=value : ");
	}
	user_in = readline("unset NAME : ");
	while (user_in != NULL && *user_in)
	{
		env = get_env();
		ft_unset(user_in, env);
		ft_env(1);
		user_in = readline("unset NAME : ");
	}
	
}