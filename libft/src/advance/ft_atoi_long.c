/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:36:12 by enzo              #+#    #+#             */
/*   Updated: 2025/09/06 19:40:31 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static long	check_overflow(long nb, int sign, int digit, int *error)
{
	if ((sign == 1 && nb > (LONG_MAX - digit) / 10)
		|| (sign == -1 && nb < (LONG_MIN + digit) / 10))
	{
		*error = 1;
		if (sign == 1)
			return (LONG_MAX);
		return (LONG_MIN);
	}
	return (nb * 10 + sign * digit);
}

long	ft_atoi_long(const char *str, int *error)
{
	long	nb;
	int		sign;

	*error = 0;
	sign = 1;
	nb = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = check_overflow(nb, sign, *str - '0', error);
		if (*error)
			return (nb);
		str++;
	}
	return (nb);
}
