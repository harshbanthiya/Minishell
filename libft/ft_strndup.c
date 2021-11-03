#include "libft.h"

char	*ft_strndup(char *s1, size_t len)
{
	char	*str;
	size_t	index;

	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (0);
	index = 0;
	while (index < len)
	{
		str[index] = s1[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}