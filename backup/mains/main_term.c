/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 14:50:39 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

typedef struct termios	t_term;

void	set_mode_inter(t_term *term)
{
	term->c_cc[VEOF] = 4;
	term->c_cc[VINTR] = 3;
	term->c_cc[VQUIT] = 0;
}

void	set_mode_non_inter(t_term *term)
{
	term->c_cc[VEOF] = 3;
	term->c_cc[VINTR] = 4;
	term->c_cc[VQUIT] = 28;
}

/* mode 0 : non-interactive, mode 1 : interactive */
void	term_change_mode(int term_fd, int mode)
{
	t_term	term;

	tcgetattr(term_fd, &term);
	if (mode == 0)
		set_mode_non_inter(&term);
	else if (mode == 1)
		set_mode_inter(&term);
	tcsetattr(term_fd, TCSANOW, &term);
}

static int	handle_input(char *str)
{

	// if (!name || !is_builtin(name))
	// 	return (0);
	if (!ft_strcmp(str, "0"))
		term_change_mode(1, 0);
	else if (!ft_strcmp(str, "1"))
		term_change_mode(1, 1);
	return (1);
}

int	main(int argn, char **argv, char **envp)
{
	char	*user_in;

	// envp[0] = NULL
	argn = 0;
	argv = NULL;
	signal(SIGQUIT, sig_quit);
	signal(EOF, sig_eof);
	signal(SIGINT, sig_intr);
	user_in = readline("prompt : ");
	while (user_in != NULL)
	{
		add_history(user_in);
		handle_input(user_in);
		user_in = readline("prompt : ");
	}
	return (0);
}