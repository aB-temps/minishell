/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:14:18 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 18:14:19 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "debug.h"

void	ft_env(char **env)
{
	const size_t	size = ft_tablen(env);
	size_t			i;

	i = 0;
	while (i < size)
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}
