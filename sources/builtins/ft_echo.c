/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:14:21 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/09 02:39:44 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdint.h>

static void	parse_param(char **args, uint8_t *param_state, size_t *i,
		size_t args_qty)
{
	size_t	j;
	uint8_t	current_param;

	if (args[*i][0] != '-' || !args[*i][1])
		return ;
	current_param = UNSET;
	while (*i < args_qty)
	{
		j = 1;
		while (args[*i][j])
		{
			if (args[*i][j] == 'n')
				current_param = ENABLED;
			else
			{
				current_param = DISABLED;
				return ;
			}
			++j;
		}
		if (*param_state == DISABLED)
			*param_state = current_param;
		++(*i);
	}
}

int	ft_echo(char **args)
{
	const size_t	args_qty = ft_tablen(args);
	size_t			i;
	uint8_t			n_param;

	i = 1;
	n_param = DISABLED;
	if (i != args_qty)
		parse_param(args, &n_param, &i, args_qty);
	while (i < args_qty)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (i < args_qty - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		++i;
	}
	if (n_param != ENABLED)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
