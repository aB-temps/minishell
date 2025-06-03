/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:41:15 by enchevri          #+#    #+#             */
/*   Updated: 2025/06/03 17:48:51 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

char	*ft_strndup(char *s, size_t n)
{
	char	*ns;
	size_t	i;

	i = 0;
	ns = malloc(sizeof(char) * n + 1);
	if (!ns)
		return (NULL);
	while (s[i] && i < n)
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = '\0';
	return (ns);
}
