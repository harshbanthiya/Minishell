#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != 0)
			last = last->next;
		last->next = new;
	}
}