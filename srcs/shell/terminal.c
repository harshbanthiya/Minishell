/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/02 16:28:15 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	init_terms(t_shell *sh, int term_fd)
{
	t_term	term;

	tcgetattr(term_fd, &sh->def_term);
	tcgetattr(term_fd, &term);
	set_mode_inter(&term);
	tcsetattr(term_fd, TCSANOW, &term);
}

/* should return the current terminal fd; need a tracked terminal fd */
int	term_get_active_fd(void)
{
	return (1);
}

void	term_restore_default(int term_fd)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh == NULL)
		return ;
	tcsetattr(term_fd, TCSANOW, &sh->def_term);
}

void print_welcome(void)
{
    ft_putstr_fd("\033[36;36;33m𝓶 𝓲𝓷𝓲𝓼𝓱𝓮𝓵𝓵\033[36;36;20m\n", 1);
    ft_putstr_fd("\033[36m", 1);
    ft_putstr_fd("Powered by the brain cells of ", 1);
    ft_putstr_fd("\033[35m@sfournie\033[0m ", 1);
    ft_putstr_fd("and \033[35m@hbanthiy\033[0m.\n", 1);
    // ft_putstr_fd("DIR:", 4);
    // //ft_putstr_fd("\033[0m", 1);
    // //ft_putstr_fd("\n", 1);
    // ft_putstr_fd("\033[3m", 1);
    // ft_putstr_fd("\033[36;36;20m", 1); //Change values here to see a different colored arrow 
    // ft_putstr_fd("> ", 1);
    // ft_putstr_fd("\033[0m", 1);
    return ;
}

char    *get_prompt(void)
{
    char    *prompt;

    prompt = ft_calloc(100, sizeof(char));
    ft_strlcat(prompt, get_pwd(), 96);
    ft_strlcat(prompt, " > ", 100);
    ft_putstr_fd("\033[0m", 1);
    return (prompt);
}

char    *ft_readline(void)
{
    char    *user_in;
    char    *prompt;
    
    prompt = get_prompt();
    user_in = readline(prompt);
    ft_free(prompt);
    return (user_in);
}
