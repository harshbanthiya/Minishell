/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_wild.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/09 16:49:30 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	<dirent.h>

typedef struct	dirent	t_dirent;

// int	ft_wildcmp(char *str, char *wild)
// {
// 	int	last_i;
// 	int	last_j;
// 	int	i;
// 	int	j;
// 	if (!str || !wild || !*str || !*wild)
// 		return (0);
// 	last_i = ft_strlen(str) - 1;
// 	last_j = ft_strlen(wild) - 1;
// 	i = 0;
// 	j = 0;
// 	while (wild[j] && wild[j] != '*')
// 		if (str[i++] != wild[j++])
// 			return (0);
// 	if (!wild[j] && !str[i])
// 		return (1);
// 	while (wild[last_j] && wild[last_j] != '*')
// 		if (str[last_i--] != wild[last_j--])
// 			return (0);
// 	while (wild[j] == '*' && wild[j + 1] == '*')
// 		j++;
// 	if (j >= last_j)
// 		return (1);
// 	while (i < last_i)
// 	{
// 		if (ft_wildcmp(&str[i], &wild[j + 1]))
// 			return (1);
// 		i++;
// 	}
// 	return(0);
// }

// int	ft_wildcmp(char *str, char *wild)
// {
// 	int	last_i;
// 	int	last_j;
// 	if (!str || !wild || !*str || !*wild)
// 		return (0);
// 	last_i = ft_strlen(str) - 1;
// 	last_j = ft_strlen(wild) - 1;
// 	while (wild[last_j] && wild[last_j] != '*')
// 		if (str[last_i--] != wild[last_j--])
// 			return (0);
// 	while (*wild && *wild != '*')
// 		if (*(str++) != *(wild++))
// 			return (0);
// 	if (!*wild && !str)
// 		return (1);
// 	while (*wild == '*' && *(wild + 1) == '*')
// 		wild++;
// 	if (!*wild || !*(wild + 1))
// 		return (1);
// 	while (*str)
// 	{
// 		if (ft_wildcmp(ft_strchr(str, *(wild + 1)), wild + 1))
// 			return (1);
// 		str++;
// 	}
// 	return(0);
// }

int	ft_wildcmp(char *str, char *wild, int i, int j)
{
	int	n;

	n = 0;
	if (!str[i] && !wild[j])
		return (1);
	else if (wild[j] == '*')
	{
		if (!wild[j + 1])
			return (1);
		while (str[i] != '\0')
		{
			if (ft_wildcmp(str, wild, i++, j + 1))
				return (1);
			else
				n++;
		}
		return (ft_wildcmp(str, wild, i, j + 1));
	}
	else if (str[i] != wild[j])
		return (0);
	else
		return (ft_wildcmp(str, wild, i + 1, j + 1));
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
		if (entry->d_name[0] != '.' && ft_wildcmp(entry->d_name, str, 0, 0))
		{
			temp = ft_calloc(ft_strlen(wildstr) + 2, sizeof(char));
			if (wildstr != NULL)
				ft_strlcat(temp, wildstr, ft_strlen(wildstr) + 1);
			ft_strlcat(temp, " ", ft_strlen(temp) + 2);
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