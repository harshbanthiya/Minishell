/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:42:48 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/12 16:43:22 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	var_is_valid_key(char *env_key)
{
	int	idx;

	idx = 0;
	if (env_key && (*env_key == '_' || ft_isalpha(env_key[idx])))
	{
		idx++;
		while (env_key[idx] != '\0')
		{
			if (!ft_isalnum(env_key[idx]) && env_key[idx] != '_')
				return (FALSE);
			idx++;
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

void	*free_var(void *ptr)
{
	t_var	*var;

	var = (t_var *)ptr;
	if (var != NULL)
	{
		if (var->key != NULL)
			ft_free(var->key);
		if (var->value != NULL)
			ft_free(var->value);
		ft_free(ptr);
	}
	return (NULL);
}
