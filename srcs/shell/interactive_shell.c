/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 22:22:08 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/17 07:59:04 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/readline/readline.h"
#include "../../includes/readline/history.h"
#include "../../includes/minishell.h"

void	execute_seqcmd(t_parse_ast *cmdline)
{
	t_parse_ast			*seqcmd;

	seqcmd = cmdline->content.command_line->seqcmd_node;
	//set_sighandlers_during_execution();
	invoke_sequential_commands(seqcmd);
	if (g_shell.signal_child_received)
	{
		if (g_shell.signal_child_received == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)", 18);
		write(STDOUT_FILENO, "\n", 1);
		set_status(128 + g_shell.signal_child_received);
	}
	//set_shell_sighandlers();
}

bool	is_invalid_input_str(char *input_str)
{
	while (*input_str)
	{
		if (*input_str & 0x80 || (unsigned char)*input_str > ' ')
			return (true);
		input_str++;
	}
	return (false);
}

void	show_parse_err(char *input_str)
{
	if (is_invalid_input_str(input_str))
	{
		put_err_msg("Parse error.");
		set_status(1);
	}
}

t_parse_ast	*get_cmdline_from_input_str(char *input_str)
{
	t_token				tok;
	t_parse_buffer		buf;
	t_parse_ast			*cmdline;

	init_buffer_with_string(&buf, input_str);
	buf.size++;
	buf.buffer[ft_strlen(input_str)] = '\n';
	scan_init_token(&tok);
	scan_get_token(&buf, &tok);
	cmdline = parse_command_line(&buf, &tok);
	free(tok.text);
	return (cmdline);
}

int	interactive_shell(void)
{
	char		*user_in;
	t_parse_ast	*root;

	//sh_change_mode(get_shell(), 1);
	print_welcome();
	user_in = ft_readline();
	while (user_in)
	{
		if (*user_in)
			add_history(user_in);
		root = get_cmdline_from_input_str(user_in);
		if (!root)
			show_parse_err(user_in);
		else
		{
			execute_seqcmd(root);
			parse_free_all_ast();
		}
		free(user_in);
		user_in = ft_readline();
	}
	write(1, "exit\n", 5);
	//free_shell();
	return (0);
}
