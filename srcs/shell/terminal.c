/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/18 15:26:10 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

void	print_welcome(void)
{
	ft_putstr_fd("\033[1;96mMinishell: \033[0m", 1);
	ft_putstr_fd("\033[1;34m", 1);
	ft_putstr_fd("Powered by the brain cells of ", 1);
	ft_putstr_fd("\033[1;34m@sfournie and \033[0m", 1);
	ft_putstr_fd("\033[1;34m@hbanthiy\033[0m.\n", 1);
	// ft_putstr_fd("DIR:", 4);
	// //ft_putstr_fd("\033[0m", 1);
	// //ft_putstr_fd("\n", 1);
	// ft_putstr_fd("\033[3m", 1);
	// ft_putstr_fd("\033[36;36;20m", 1); //Change values here to see a different colored arrow 
	// ft_putstr_fd("> ", 1);
	// ft_putstr_fd("\033[0m", 1);
	return ;
}

char	*get_prompt(void)
{
	t_shell *sh;
	char    *prompt;

	sh = get_shell();
	if (!sh)
		return (NULL);
	prompt = sh->prompt;
	ft_bzero(prompt, 100);
	ft_strlcat(prompt, "\033[1;91m", 6);
	ft_strlcat(prompt, ft_strrchr(get_pwd(), '/'), 90);
	ft_strlcat(prompt, "\033[0m", 3);
	ft_strlcat(prompt, "\033[1;106m", 7);
	ft_strlcat(prompt, " > ", 5);	ft_strlcat(prompt, "\033[0m", 100);
	return (prompt);
}

char	*ft_readline(void)
{
	char	*user_in;

	user_in = readline(get_prompt());
	return (user_in);
}
