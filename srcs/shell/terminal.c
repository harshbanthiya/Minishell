/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/03 16:21:23 by hbanthiy         ###   ########.fr       */
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
	char	*pwd;

	sh = get_shell();
	if (!sh)
		return (NULL);
	prompt = sh->prompt;
	ft_strcpy(prompt, PROMPT);
	ft_strlcat(prompt, C_CYAN, PROMPT_SIZE);
	pwd = ft_strdup(ft_strrchr(get_pwd(), '/'));
	if (ft_strlen(pwd) > 15)
	{
		pwd[20] = '\0';
		ft_strcat(prompt, pwd);
		ft_strcat(prompt, "..");
	}
	else
		ft_strlcat(prompt, ft_strrchr(get_pwd(), '/'), PROMPT_SIZE);
	ft_free(pwd);
	append_git(prompt);
	ft_strlcat(prompt, C_CYAN, PROMPT_SIZE);
	ft_strlcat(prompt, " > ", PROMPT_SIZE);
	ft_strlcat(prompt, C_NO, PROMPT_SIZE);
	return (prompt);
}

char	*ft_readline(void)
{
	char	*user_in;

	user_in = readline(get_prompt());
	return (user_in);
}

void	exit_shell(void)
{
	parse_free_all_ast();
	free_shell();
	exit(g_shell.exit_flag);
}
