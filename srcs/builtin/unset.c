/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:51 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/19 12:58:57 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

int	ft_unset_var(char *key, t_dlist **lst)
{
	t_var	*var;
	t_dlist	*temp;

	if (key == NULL || lst == NULL)
		return (0);
	temp = *lst;
	while (temp != NULL)
	{
		var = (t_var *)temp->content;
		if (!ft_strncmp(key, var->key, ft_strlen(key)))
		{
			if (temp->prev == NULL)
				*lst = temp->next;
			lst_remove_node(temp, free_var);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static void	put_unset_errmsg(char *cmd_name, char *keyname)
{
	char	*tmp;
	char	*errmsg;

	tmp = ft_strjoin("`", keyname);
	if (!tmp)
		put_minish_err_msg_and_exit(1, cmd_name, "ft_strjoin() failed");
	errmsg = ft_strjoin(tmp, "': not a valid identifier");
	free(tmp);
	if (!errmsg)
		put_minish_err_msg_and_exit(1, cmd_name, "ft_strjoin() failed");
	put_minish_err_msg(cmd_name, errmsg);
	free(errmsg);
}

int	ft_unset(char **argv)
{
	int		i;
	int		exit_code;
	t_dlist	**env;
	bool	is_key_ok;

	exit_code = 0;
	env = get_env();
	is_key_ok = true;
	i = 1;
	if (env && argv && argv[1] && argv[1][0] == '-')
		return (error_builtin("unset", argv[1], "invalid option", 2));
	while (env && argv[i])
	{
		if (var_is_valid_key(argv[i]))
			ft_unset_var(argv[i], env);
		else
		{
			is_key_ok = false;
			put_unset_errmsg(argv[0], argv[i]);
		}
		i++;
	}
	if (!env || !is_key_ok)
		return (1);
	return (0);
}
