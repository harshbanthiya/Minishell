/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:44:34 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:05:15 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void	parse(t_dlist *token_list, t_node **node)
{
	global_current_token_node = token_list;
	*node = cmd_line();
	//if (global_current_token_node != NULL)
		//printf("syntax error near unexpected token: \'%s\'\n", \
		((t_token *)global_current_token_node->content)->data);
}

static t_node	*get_tree(char *line)
{
	t_dlist		*token_list;
	t_node		*output;

	token_list = NULL;
	if (make_token_list(&token_list, line) < 0)
	{
		printf("Error: wrong token\n");
		return (NULL);
	}
	else
		parse(token_list, &output);
	return (output);
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
	t_node			*root;
	size_t			len;
	
	len = ft_strlen(cmdstr);
	init_buffer_with_cmdstr(&buff, cmdstr);
	buff.size++;
	buff.buffer[len] = '\n';
	scan_init_token(&tok);
	scan_get_token(&buff, &tok);
	root = get_tree(cmdstr);
	if (root)
	{
		execute_tree(root, get_env());
		return (0);
	}
	else
	{
		put_err_msg("Parse error.");
		return (1);
	}
}

int	interactive_shell(void)
{
	char	*user_in;
	t_node	*root;

	init_signals();
	print_welcome();
	user_in = ft_readline();
	while (user_in)
	{
		if (*user_in)	
			add_history(user_in);
		root = get_tree(user_in);
		if (!root)	
			show_parse_err(user_in);
		else
		{
			execute_tree(root, get_env());
			//parse_free_all_ast();
		}
		free(user_in);
		user_in = ft_readline();
	}
	free(user_in);
	free_shell();
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	init_shell(envp);
	if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
		return (do_command(argv[2]));
	interactive_shell();
}
