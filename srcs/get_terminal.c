/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:43:20 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/24 18:03:43 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_term	*get_saved_term(void)
{
	t_shell	*sh;

	sh = get_shell();
	return (sh->saved_term);
}

t_term	*get_def_term(void)
{
	t_shell	*sh;

	sh = get_shell();
	return (sh->def_term);
}

t_term	*get_active_term(void)

{
	t_shell	*sh;

	sh = get_shell();
	return (sh->active_term);
}
