/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/23 21:06:44 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

void	print_welcome(void)
{
	ft_putstr_fd(C_CYAN, 1);
	ft_putstr_fd("Minishell: ", 1);
	ft_putstr_fd(C_BLUE, 1);
	ft_putstr_fd("Powered by the brain cells of ", 1);
	ft_putstr_fd("@sfournie and @hbanthiy.\n", 1);
	ft_putstr_fd(C_NO, 1);
	return ;
}

char	*get_prompt(void)
{
	t_shell	*sh;
	char	*prompt;

	sh = get_shell();
	if (!sh)
		return (NULL);
	prompt = sh->prompt;
	ft_strcpy(prompt, PROMPT);
	ft_strlcat(prompt, C_CYAN, 150);
	ft_strlcat(prompt, ft_strrchr(get_pwd(), '/'), 150);
	append_git(prompt);
	ft_strlcat(prompt, C_CYAN, 150);
	ft_strlcat(prompt, " > ", 150);
	ft_strlcat(prompt, C_NO, 150);
	return (prompt);
}

char	*ft_readline(void)
{
	char	*user_in;

	user_in = readline(get_prompt());
	return (user_in);
}
