/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:30:06 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:42:07 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ms_parse.h"

t_parse_hdoc_list   *parse_concat_heredocs(
    t_parse_ast *head, t_parse_ast *tail)
{
    t_parse_hdoc_list   *list;

    if (!head || !head->heredocs)
    {
        if (tail)
            return (tail->heredocs);
        else 
            return (NULL);
    }
    list = head->heredocs;
    while (list->next)
        list = list->next;
    if (tail)
        list->next = tail->heredocs;
    return (head->heredocs);
}

t_parse_hdoc_list   *parse_new_heredocs(
    t_parse_node_redirection *redirection)
{
    t_parse_hdoc_list   *list;
    
    list = malloc(sizeof(t_parse_hdoc_list));
    if (!list)
        parse_fatal_error();
    list->redirection = redirection;
    list->next = NULL;
    return (list);
}

void    parse_free_heredocs(t_parse_hdoc_list *list)
{
    if (!list)
        return ;
    parse_free_heredocs(list->next);
    free(list);
}