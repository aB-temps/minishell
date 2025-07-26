/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:14:21 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 22:07:06 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	is_valid_echo_param(char c)
{
	const char	valid_params[3] = {'e', 'E', 'n'};
	size_t		i;

	i = 0;
	while (i < 3)
	{
		if (c == valid_params[i])
			return (true);
		else
			i++;
	}
	return (false);
}

static void	parse_param(char *arg, bool *n_param, size_t *i)
{
	size_t	j;

	j = 0;
	while (arg[j] && arg[j] != '-')
		j++;
	if (!arg[j] || !arg[j + 1])
		return ;
	j++;
	// if (!arg[j])
	// 	return ;
	while (arg[j])
	{
		if (is_valid_echo_param(arg[j]))
			*n_param = (arg[j] == 'n');
		else
		{
			*n_param = false;
			return ;
		}
		j++;
	}
	(*i)++;
}

void	ft_echo(char **args)
{
	const size_t	args_qty = ft_tablen(args);
	bool			n_param;
	size_t			i;
	size_t			j;

	i = 1;
	n_param = false;
	while (args[i] && ft_strchr(args[i], '-'))
	{
		j = i;
		parse_param(args[i], &n_param, &i);
		if (i == j)
			break ;
	}
	while (i < args_qty)
	{
		printf("%s", args[i]);
		if (i < args_qty - 1)
			printf(" ");
		i++;
	}
	if (!n_param)
		printf("\n");
}
