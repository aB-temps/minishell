/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 06:05:24 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/29 06:05:25 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	printf("Formatted Content :\n");
	while (tab[i])
	{
		printf("[%i]: '%s'\n", i, tab[i]);
		i++;
	}
	printf("\n");
}
