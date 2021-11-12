/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:05:32 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/08 22:15:12 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TREE_H
# define MS_TREE_H

typedef struct s_node
{
	int				type;
	char			*data;
	struct s_node	*left_child;
	struct s_node	*right_child;
}t_node;

typedef enum e_parse_ast_type
{
	NODE_PIPE = 100,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_CMDPATH,
	NODE_ARGUMENT,
	NODE_REDIRECT_DOUBLEOUT,
	NODE_REDIRECT_DOUBLEIN,
	NODE_DATA,
	NODE_SEQ,
}t_parse_ast_type;

#endif