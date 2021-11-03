/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_top.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:13:21 by sucho             #+#    #+#             */
/*   Updated: 2021/02/01 00:10:20 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*commandline(void)
{
	t_node	*node;
	t_list	*save;

	save = g_curtok;
	if ((g_curtok = save, node = commandline_1()) != NULL)
		return (node);
	if ((g_curtok = save, node = commandline_2()) != NULL)
		return (node);
	if ((g_curtok = save, node = commandline_3()) != NULL)
		return (node);
	return (NULL);
}

t_node	*commandline_1(void)
{
	t_node	*job_node;
	t_node	*cmdline_node;
	t_node	*result;

	if ((job_node = job()) == NULL)
		return (NULL);
	if (!term(SEMICOLON, NULL))
	{
		node_delete(job_node);
		return (NULL);
	}
	if ((cmdline_node = commandline()) == NULL)
	{
		node_delete(job_node);
		return (NULL);
	}
	if (!(result = malloc(sizeof(*result))))
		return (NULL);
	node_set_data(result, ";");
	node_set_type(result, NODE_SEQ);
	node_attach_branch(result, job_node, cmdline_node);
	return (result);
}

t_node	*commandline_2(void)
{
	t_node *job_node;
	t_node *result;

	if ((job_node = job()) == NULL)
		return (NULL);
	if (!term(SEMICOLON, NULL))
	{
		node_delete(job_node);
		return (NULL);
	}
	if (!(result = malloc(sizeof(*result))))
		return (NULL);
	node_set_data(result, ";");
	node_set_type(result, NODE_SEQ);
	node_attach_branch(result, job_node, NULL);
	return (result);
}

t_node	*commandline_3(void)
{
	return (job());
}

t_node	*job(void)
{
	t_node	*node;
	t_list	*save;

	save = g_curtok;
	if ((g_curtok = save, node = job_1()) != NULL)
		return (node);
	if ((g_curtok = save, node = job_2()) != NULL)
		return (node);
	return (NULL);
}

t_node	*job_1(void)
{
	t_node	*command_node;
	t_node	*job_node;
	t_node	*result;

	if ((command_node = command()) == NULL)
	{
		return (NULL);
	}
	if (!term(PIPE, NULL))
	{
		node_delete(command_node);
		return (NULL);
	}
	if ((job_node = job()) == NULL)
	{
		node_delete(command_node);
		return (NULL);
	}
	if (!(result = malloc(sizeof(*result))))
		return (NULL);
	node_set_data(result, "|");
	node_set_type(result, NODE_PIPE);
	node_attach_branch(result, command_node, job_node);
	return (result);
}

t_node	*job_2(void)
{
	return (command());
}
