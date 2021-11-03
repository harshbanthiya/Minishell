/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 21:40:24 by cbaek             #+#    #+#             */
/*   Updated: 2021/02/01 13:56:55 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		put_prompt(void)
{
	char	cwd[100];

	getcwd(cwd, 99);
	ft_putstr_fd("\033[36m", 1);
	ft_putstr_fd("DIR:", 4);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\033[0m", 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\033[3m", 1);
	ft_putstr_fd("eo", 1);
	ft_putstr_fd("\033[38;5;20m", 1);
	ft_putstr_fd("> ", 1);
	ft_putstr_fd("\033[0m", 1);
}

// static void	free_token_list(t_list *token_list)
// {
// 	if (token_list != NULL)
// 	{
// 		free(((t_token *)(token_list->content))->data);
// 		free(token_list->content);
// 		free_token_list(token_list->next);
// 		free(token_list);
// 	}
// }

/*
** put_result()
** 결과 출력(테스트용)
** TODO: 함수 삭제시 stdio.h 헤더 삭제
*/

// static int	put_result(t_list *token_list)
// {
// 	t_list *token_head;

// 	token_head = token_list;
// 	while (token_head)
// 	{
// 		printf("TYPE:%.3d CONTENT: [%s]\n", \
// 				((t_token *)(token_head->content))->type, \
// 				((t_token *)(token_head->content))->data);
// 		token_head = token_head->next;
// 	}
// 	return (0);
// }

static void		parse(t_list *token_list, t_node **node)
{
	g_curtok = token_list;
	*node = commandline();
	if (g_curtok != NULL)
	{
		printf("syntax error near unexpected token: \'%s\'\n", \
				((t_token *)g_curtok->content)->data);
	}
}

static t_node	*get_astree(char *line) //env_list 필요
{
	t_list	*token_list;
	t_node	*output;

	token_list = NULL;
	if (set_token_list(&token_list, line) < 0)
	{
		write(1, "Error: wrong token\n", 19);
		return (NULL);
	}
	else
		parse(token_list, &output);
	return (output);
}

static void		hook(int signo)
{
	if (signo == SIGINT)
	{
		global_exit_code = 1;
		ft_putstr_fd("\b\b  \n", 1);
		put_prompt();
	}
	else if (signo == SIGTSTP || signo == SIGQUIT)
		ft_putstr_fd("\b\b​​  \b\b", 1);
}

int				main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*env_list;
	t_node	*astree_root;

	if (!argc || !(*argv[0]))
		return (-1);
	env_list = set_env_list(envp);
	g_exit_code = 0;
	signal(SIGQUIT, hook);
	signal(SIGINT, hook);
	while (1)
	{
		put_prompt();
		line = readline();
		astree_root = get_astree(line); // env_list 필요
		if (astree_root)
			execute_tree(astree_root, &env_list);
		// print_env_list(env_list);
		free(line);
		// write(1, "\n", 1);
	}
	free(line);
	ft_lstclear(&env_list, free);
	return (0);
}
