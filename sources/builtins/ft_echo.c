/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:14:21 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/08 12:57:03 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	is_valid_echo_param(char c)
{
	const char	valid_params[1] = {'n'};
	size_t		i;

	i = 0;
	while (i < 1)
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
	while (arg[j] && is_whitespace(arg[j]) && arg[j] != '-')
		j++;
	if (!arg[j] || !arg[j + 1])
		return ;
	j++;
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

int	ft_echo(char **args)
{
	const size_t	args_qty = ft_tablen(args);
	bool			n_param;
	size_t			i;

	i = 1;
	n_param = false;
	if (args[i] && ft_strchr(args[i], '-'))
		parse_param(args[i], &n_param, &i);
	while (i < args_qty)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (i < args_qty - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!n_param)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
