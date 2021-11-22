/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:44:34 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/22 16:29:18 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_parse.h"
#include "../libft/libft.h"

t_shell		g_shell;

void	die(void)
{
	int	*nullpo;

	nullpo = NULL;
	nullpo[0xdead] = 1;
}

int	invoke_sequential_commands(t_parse_ast *seqcmd)
{
	t_command		*new;
	int				status;

	while (seqcmd && seqcmd->content.sequential_commands->pipcmd_node)
	{
		if (seqcmd->type != ASTNODE_SEQ_COMMANDS)
			die();
		new = pipcmd2cmd(
				seqcmd->content.sequential_commands->pipcmd_node
				->content.piped_commands);
		if (new)
		{
			status = cmd_exec_commands(new);
			cmd_free_cmd(new);
		}
		seqcmd = seqcmd->content.sequential_commands->rest_node;
	}
	return (status);
}

void	init_buffer_with_string(t_parse_buffer *buff, char *str)
{
	size_t	len;

	len = ft_strlen(str);
	buff->cur_pos = 0;
	buff->size = len;
	buff->scan_state = SCANSTATE_NORMAL;
	ft_strlcpy(buff->buffer, str, len + 1);
	buff->getc = NULL;
	buff->ungetc = NULL;
}

int	do_command(char *cmdstr)
{
	t_parse_buffer	buff;
	t_parse_ast		*cmdline;
	t_token			tok;
	t_parse_ast		*seqcmd;
	size_t			len;

	len = ft_strlen(cmdstr);
	init_buffer_with_string(&buff, cmdstr);
	buff.size++;
	buff.buffer[len] = '\n';
	scan_init_token(&tok);
	scan_get_token(&buff, &tok);
	cmdline = parse_command_line(&buff, &tok);
	free(tok.text);
	if (cmdline)
	{
		seqcmd = cmdline->content.command_line->seqcmd_node;
		return (invoke_sequential_commands(seqcmd));
	}
	else
	{
		put_err_msg("Parse error.");
		return (2);
	}
}

int	main(int argc, char **argv, char **envp)
{
	sh_init(envp);
	if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
	{
		if (!argv[2][0])
			return (0);
		return (do_command(argv[2]));
	}
	interactive_shell();
}
