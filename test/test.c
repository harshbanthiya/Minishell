/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:24:24 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:49:34 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int	success_count = 0;
int	fail_count = 0;

bool	test_check(int64_t val, const char *msg)
{
	if (val)
	{
		success_count++;
		printf("  ✔ %s\n", msg);
		return (true);
	}
	else
	{
		fail_count++;
		printf("  ✖ %s\n", msg);
		return (false);
	}
}

int	print_result()
{
	printf("✔: %d ✖: %d\n", success_count, fail_count);
	return (fail_count);
}