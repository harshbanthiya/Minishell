#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t size;
	t_list *temp;

	size = 0;
	temp = lst;
	while (temp != 0)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}