#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *lst;

	if ((lst = (t_list *)malloc(sizeof(t_list))) == 0)
		return (0);
	lst->content = content;
	lst->next = 0;
	return (lst);
}