/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 15:58:32 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SHELL_H
# define MS_SHELL_H
# include "minishell.h"

typedef struct termios	t_term;

/* Contain every pertinent informations worth being accessible globally */
/* sd_mode : 1 = interactive, 0 = non-interactive */
/* def_term : Default terminal (to be restored at the end!) */
typedef struct s_shell
{
	t_dlist	*env;
	t_term	def_term;
	int		sh_mode;
	char	**builtins;
	char	*pwd;
}				t_shell;

/* Master init function. Makes all the init calls needed. */
void	init_shell(char **envp);
t_shell	*get_shell(void);
void	sh_change_mode(int mode);
int		get_sh_mode(void);
void	set_mode_inter(t_term *term);
void	set_mode_non_inter(t_term *term);
void	exit_shell(void);
void	free_shell(void);

/* Terminal */
void	init_terms(t_shell *sh, int term_fd);
void	term_save_state(int term_fd);
void	term_restore_default(int term_fd);
int		term_get_active_fd(void);
/* End terminal */

#endif