/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/27 11:39:38 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SHELL_H
# define MS_SHELL_H
# include "minishell.h"

# define C_NO	"\001\e[0m\002"
# define C_BLUE	"\001\e[1;34m\002"
# define C_RED	"\001\e[1;91m\002"
# define C_CYAN	"\001\e[1;36m\002"
# define PROMPT_SIZE 150

/* Contain every pertinent informations worth being accessible globally */
/* sd_mode : 1 = interactive, 0 = non-interactive */
typedef struct s_shell
{
	t_dlist	*env;
	int		sh_mode;
	char	*pwd;
	int		signal_child_received;
	int		heredoc_interruption;
	int		status;
	char	prompt[PROMPT_SIZE];
}				t_shell;

/* Master init function. Makes all the init calls needed. */
void	sh_init(char **envp);
t_shell	*get_shell(void);
void	sh_change_mode(t_shell *sh, int mode);
int		sh_get_mode(void);
void	exit_shell(void);
void	free_shell(void);
char	*ft_readline(void);
/* Prompt needs to be freed */
char	*get_prompt(void);
void	append_git(char *prompt);
void	print_welcome(void);
/* End terminal */

#endif