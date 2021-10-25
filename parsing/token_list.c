/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:47:32 by sfournie          #+#    #+#             */
/*   Updated: 2021/09/28 20:23:03 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_tok	*ft_new_tok(char *str)
{	
	t_tok	*tok;

	tok = (t_tok *)malloc(sizeof(t_tok));
	if (tok == NULL)
		return (NULL);
	tok->value = str;
	tok->next = NULL;
	return (tok);
}

void	ft_add_front(t_tok *tok, t_tok *new)
{
	if (tok == NULL)
		tok = new;
	else if (new != NULL)
	{
		new->next = tok;
		tok = new;
	}
}

void	ft_add_back(t_tok **tok, t_tok *new)
{
	if (*tok == NULL)
		*tok = new;
	else if (new != NULL)
	{
		if ((*tok)->next != NULL)
			ft_add_back(&(*tok)->next, new);
		else
			(*tok)->next = new;
	}
}

void	*ft_free_tokens(t_tok *tok)
{
	int	i;

	if (tok != NULL)
	{
		if (tok->next != NULL)
			ft_free_tokens(tok->next);
		if (tok->value != NULL)
			free (tok->value);
		free (tok);
	}
	return (NULL);
}

void	ft_print_tokens(t_tok *tok)
{
	t_tok	*temp;

	temp = tok;
	while (temp != NULL)
	{	
		if (temp->value != NULL)
		{
			printf("%s\n", temp->value);
		}
		temp = temp->next;
	}
}
