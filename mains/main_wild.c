/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_wild.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/09 11:58:02 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<dirent.h>

typedef struct	dirent	t_dirent;

int	ft_wildcmp(char *str1, char *str2)
{
	if (!str1 || !str2 || !*str1 || !*str2)
		return (0);
	while (*str1 == *str2 || *str2 == '*')
	{
		if (*str1 == *str2 && !*str2)
			return (1);
		else if (*str2 == '*' && *(str2 + 1) == '*')
			str2++;
		else if (*str1 == *(str2 + 1))
			str2++;
		else if (*str1 == *str2)
		{
			str1++;
			str2++;
		}
		else if (*str2 != '*' && *str1 != *str2)
			break;
		else if (!*str1)
			break;
		else
			str1++;
	}
	return (0);
}

char	*parse_expand_wild(char *str)
{
	DIR			*pwd;
	t_dirent	*entry;
	char		*wildstr;
	char		*temp;
	
	pwd = opendir(get_pwd());
	entry = readdir(pwd);
	wildstr = NULL;
	while (entry)
	{
		if (ft_wildcmp(entry->d_name, str))
		{
			if (wildstr == NULL)
				temp = ft_calloc(1, sizeof(char));
			else
			{
				temp = ft_calloc(ft_strlen(wildstr) + 2, sizeof(char));
				ft_strlcat(temp, wildstr, ft_strlen(wildstr) + 1);
				ft_strlcat(temp, " ", ft_strlen(temp) + 2);
			}
			ft_free(wildstr);
			wildstr = ft_strfuse(temp, ft_strdup(entry->d_name));
		}
		entry = readdir(pwd);
	}
	closedir(pwd);
	return (wildstr);
}

static int	handle_input(char *str)
{
	char *wildstr;

	wildstr = parse_expand_wild(str);
	ft_putendl_fd(wildstr, 1);
	ft_free(wildstr);
	return (0);
}

int	main(int argn, char **argv, char **envp)
{
	char	*user_in;

	// envp[0] = NULL;
	argn = 0;
	argv = NULL;
	init_shell(envp);
	print_welcome();
	user_in = ft_readline();
	while (user_in != NULL && *user_in)
	{
		add_history(user_in);
		handle_input(user_in);
		ft_free(user_in);
		user_in = ft_readline();
	}
	ft_free(user_in);
	free_shell();
}