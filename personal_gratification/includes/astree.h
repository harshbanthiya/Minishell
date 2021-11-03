/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:48:28 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/28 17:54:18 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

# include "minishell.h"

enum						e_token_type {
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	TOKEN = -1,
};

void						ast_init_branch(t_node *head, t_node *left, \
									t_node *right);
void						ast_set_type(t_node *node, t_nodetype type);
void						ast_set_data(t_node *node, char *data);
void						ast_delete(t_node *node);
void						parse(t_list *toekn_list, t_node **syntax_tree);
int							term(int token_type, char**buffer_ptr);
bool						term_token(t_list **list_ptr, int token_type, \
									char **arg);
bool						term_redirection(t_list **list_ptr, \
									char **filename, int *set_type);
t_node						*command_line();
t_node						*command_line1();
t_node						*job();
t_node						*job1();
t_node						*command();
t_node						*command1();
t_node						*simple_command();
t_node						*simple_command1();
t_node						*token_list();
t_node						*token_list1();
t_node						*token_list2();

#endif
