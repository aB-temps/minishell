/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:39:02 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/27 19:47:52 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t				i;
	size_t				count;
	unsigned long long	*s_bis;

	i = 0;
	count = 0;
	s_bis = (unsigned long long *)s;
	if (n >= sizeof(unsigned long long))
	{
		while (count < n - sizeof(unsigned long long))
		{
			*(s_bis + i++) = 0;
			count += sizeof(unsigned long long);
		}
	}
	while (count < n)
		*(((unsigned char *)s_bis) + count++) = 0;
}
