/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:01:07 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/17 07:59:41 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
# include	<dirent.h>

typedef struct	dirent	t_dirent;

static int	ft_countsplit(char **split)
{
	int	count;

	count = 0;
	while (split && *split)
	{
		split++;
		count++;
	}
	return (count);
}

static int	ft_wildcmp(char *str, char *wild, int i, int j)
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

static char	**ft_split_fuse(char **split1, char **split2)
{
	char	**fused;
	int		size;
	int		i;
	int		j;

	size = ft_countsplit(split1) + ft_countsplit(split2);
	fused = (char **)ft_calloc(size + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (split1[i])
		fused[j++] = split1[i++];
	i = 0;
	while (split2[i])
		fused[j++] = split2[i++];
	fused[j] = NULL;
	ft_free(split1);
	ft_free(split2);
	return (fused);
}

static char	**merge_list_to_split(t_dlist *lst)
{
	char	**split;
	t_dlist	*temp;
	int		i;

	split = (char **)ft_calloc(lst_size(lst) + 1, sizeof(char *));
	temp = lst;
	i = 0;
	while (temp != NULL)
	{
		split[i++] = ft_strdup((char *)temp->content);
		temp = temp->next;
	}
	split[i] = NULL;
	return (split);
}

static char	**expand_wild(char *str)
{
	DIR			*pwd;
	t_dirent	*entry;
	t_dlist		*wild_list;
	char		**wild_split;

	pwd = opendir(get_pwd());
	entry = readdir(pwd);
	wild_list = NULL;
	while (entry)
	{
		if (entry->d_name[0] != '.' && ft_wildcmp(entry->d_name, str, 0, 0))
			lst_add_back(&wild_list, lst_new_node(ft_strdup(entry->d_name)));
		entry = readdir(pwd);
	}
	closedir(pwd);
	if (wild_list == NULL)
	{
		wild_split = (char **)ft_calloc(2, sizeof(char *));
		wild_split[0] = ft_strdup(str);
		wild_split[1] = NULL;
		return (wild_split);
	}
	wild_split = merge_list_to_split(wild_list);
	lst_clear(wild_list, ft_free);
	return (wild_split);
}

char	**exec_wild_args(char **argv)
{
	int		i;
	int		j;
	char	**wild_split;
	char	**wild_argv;

	wild_argv = (char **)ft_calloc(ft_countsplit(argv) + 1, sizeof(char *));
	if (wild_argv == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (argv && argv[i])
	{
		if (ft_strchr(argv[i], '*'))
		{
			wild_split = expand_wild(argv[i]);
		}
		else
		{
			wild_split = (char **)ft_calloc(2, sizeof(char *));
			wild_split[0] = ft_strdup(argv[i]);
			wild_split[1] = NULL;
		}
		wild_argv = ft_split_fuse(wild_argv, wild_split);
		i++;
	}
	free_split(argv);
	return (wild_argv);
}
