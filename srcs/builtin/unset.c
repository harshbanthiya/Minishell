/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:51 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/18 16:12:58 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

// // Sebas, t'es rendu ici
// static int	var_key_is_valid(char *key)
// {
// 	char	quote;
// 	int		i;

// 	if (key == NULL)
// 		return (0);
// 	i = 0;
// 	quote = '\0';
// 	while (key[i])
// 	{
// 		if (parse_is_quotes(key, i) && (quote == '\0' || quote == key[i]))
// 		{
// 			if (quote == key[i])
// 				quote = '\0';
// 			else
// 				quote = key[i];
// 		}
// 		else
// 			return (0);
// 		if (key[i] == '\\' && parse_is_escaped(key, i))
// 			return (0);
// 	}
// }

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
	if (env == NULL)
		return (1);
	//if (argv[1] == NULL)
		//return(error_builtin("unset", NULL, "not enough arguments", 1));
	i = 1;
	while (argv[i])
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
	if (!is_key_ok)
		return (1);
	return (0);
}