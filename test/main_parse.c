/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:45:14 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/19 16:29:28 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	main(int argn, char **argv, char **envp)
{
	int		flag_exit = 0;
	char	*user_input;
	char	*parsed_input;
	
	init_shell(envp);
	while (!flag_exit)
	{
		user_input = readline("write nothing to exit : ");
		// user_input = get_env_var(user_input);
		if (user_input != NULL && *user_input)
		 	add_history(user_input);
		else
			break;
		parsed_input = parse_cmdline(user_input);
		printf("%s\n", parsed_input);
		free(parsed_input);
		free(user_input);
	}
	free(user_input);
	free_shell();
	return (0);
}