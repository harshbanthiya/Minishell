/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:59:08 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:29:10 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "../../includes/ms_environment.h"
#include "../../includes/ms_execution.h"
#include "../../includes/ms_builtin.h"

t_fd_list	*fd_list_add_fd(t_fd_list **lst, int fd)
{
	t_fd_list	*new_lst;
	t_fd_list	*tmp;

	if (!lst)
		return (NULL);
	new_lst = ft_calloc(1, sizeof(t_fd_list));
	new_lst->fd = fd;
	if (!new_lst)
		return (NULL);
	if (!*lst)
		*lst = new_lst;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_lst;
	}
	return (new_lst);
}

void	fd_list_close(t_fd_list **lst)
{
	t_fd_list	*current;
	t_fd_list	*tmp;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		close(current->fd);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*lst = NULL;
}
