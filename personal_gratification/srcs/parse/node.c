/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:12:29 by sucho             #+#    #+#             */
/*   Updated: 2021/02/01 00:11:35 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_attach_branch(t_node *root, t_node *l_node, t_node *r_node)
{
	if (root == NULL)
		return ;
	root->left = l_node;
	root->right = r_node;
}

void	node_append_right(t_node **root, t_node *right)
{
	t_node *seek;

	seek = *root;
	if (!seek)
	{
		*root = right;
		return ;
	}
	while (1)
	{
		if (seek->right)
			seek = seek->right;
		else
		{
			seek->right = right;
			return ;
		}
	}
}

void	node_set_type(t_node *node, int type_num)
{
	if (node == NULL)
		return ;
	node->type = type_num;
}

void	node_set_data(t_node *node, char *token)
{
	if (node == NULL)
		return ;
	if (token != NULL)
	{
		node->data = token;
	}
}

void	node_delete(t_node *node)
{
	if (!node)
		return ;
	node_delete(node->left);
	node_delete(node->right);
	free(node);
}

void	pre_order(t_node *search)
{
	if (search)
	{
		printf("pre_order: %s \t", (char *)search->data);
		printf("node_type: %d \n", search->type);
		pre_order(search->left);
		pre_order(search->right);
	}
}

void	node_count_pipe_node(t_node *search)
{
	if (search)
	{
		if (search->type == NODE_PIPE)
			g_pipe_index++;
		node_count_pipe_node(search->left);
		node_count_pipe_node(search->right);
	}
}
