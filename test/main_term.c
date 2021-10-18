/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/18 13:23:06 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<sys/types.h>
# include	<termios.h>
# include	<signal.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<string.h>

typedef struct termios	t_term;

void	term_set_inter(t_term *term)
{
	term->c_cc[VEOF] = 4;
	term->c_cc[VINTR] = 3;
	term->c_cc[VQUIT] = 0;
}

void	term_set_non_inter(t_term *term)
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
		term_set_non_inter(&term);
	else if (mode == 1)
		term_set_inter(&term);
	tcsetattr(term_fd, TCSANOW, &term);
}

/* ctrl-c */
/* interactive mode : print new prompt on newline */
/* non-interactive mode : */
void	sig_intr(int sig_num)
{
	printf("trying to interrupt\n");
	// rl_on_new_line();
	// rl_replace_line("interrupted prompt :", 0);
	// rl_redisplay();
}

/* ctrl-d */
/* interactive : exit the shell (call exit_shell()) */
/* non-interactive : */
void	sig_eof(int sig_num)
{
	printf("trying to end of file\n");
}

/* ctrl-\ */
/* interactive mode : print new prompt on newline */
/* non-interactive mode : */
void	sig_quit(int sig_num)
{
	printf("trying to quit\n");
}

static int	handle_input(char *str)
{

	// if (!name || !is_builtin(name))
	// 	return (0);
	if (!strncmp(str, "0", 2))
		term_change_mode(1, 0);
	else if (!strncmp(str, "1", 2))
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