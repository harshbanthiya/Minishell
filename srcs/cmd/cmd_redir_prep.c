/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_prep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:58:28 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:34:41 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ms_execution.h"

t_cmd_redirection *cmd_redirection_add_back(t_cmd_redirection **reds,
    t_cmd_redirection *new_red)
{
    t_cmd_redirection   *red;
    
    new_red->next = NULL;
    red = *reds;
    if (!red)
        *reds = new_red;
    else 
    {
        while (red->next)
            red = red->next;
        red->next = new_red;
    }
    return (new_red);
}

