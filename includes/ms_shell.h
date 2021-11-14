/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/14 14:03:25 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SHELL_H
# define MS_SHELL_H
# include "minishell.h"

/* Contain every pertinent informations worth being accessible globally */
/* sd_mode : 1 = interactive, 0 = non-interactive */
typedef struct s_shell
{
	t_dlist	*env;
	int		sh_mode;
	char	**builtins;
	char	*pwd;
	int 	signal_child_received;
	int 	heredoc_interruption;
	int 	status;
	char	prompt[100];
}				t_shell;

/* Master init function. Makes all the init calls needed. */
void	init_shell(char **envp);
t_shell	*get_shell(void);
void	sh_change_mode(int mode);
int		get_sh_mode(void);
void	exit_shell(void);
void	free_shell(void);
char	*ft_readline(void);
/* Prompt needs to be freed */
char	*get_prompt(void);
void	print_welcome(void);
/* End terminal */

#endif