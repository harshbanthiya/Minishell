/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 11:58:31 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/12 23:25:12 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int	idx;

	if (!s && !*s)
		return (0);
	idx = 0;
	while (s[idx] != 0)
		idx++;
	if (c == 0)
		return ((char *)&s[idx]);
	while (idx >= 0)
	{
		if (s[idx] == c)
			return ((char *)&s[idx]);
		idx--;
	}
	return (0);
}
