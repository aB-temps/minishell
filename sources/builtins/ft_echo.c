/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:14:21 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/25 14:39:57 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static enum e_bool	is_valid_echo_param(char c)
{
	const char	valid_params[3] = {'e', 'E', 'n'};
	size_t		i;

	i = 0;
	while (i < 3)
	{
		if (c == valid_params[i])
			return (TRUE);
		else
			i++;
	}
	return (FALSE);
}

static void	parse_param(char *arg, enum e_bool *n_param, size_t *i)
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
			*n_param = FALSE;
			return ;
		}
		j++;
	}
	(*i)++;
}

int	ft_echo(char **args)
{
	const size_t	args_qty = ft_tablen(args);
	enum e_bool		n_param;
	size_t			i;
	size_t			j;

	i = 1;
	n_param = FALSE;
	while (args[i] && ft_strchr(args[i], '-'))
	{
		j = i;
		parse_param(args[i], &n_param, &i);
		if (i == j)
			break ;
	}
	while (i < args_qty)
	{
		ft_putstr_fd(args[i], 1);
		if (i < args_qty - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_param)
		ft_putstr_fd("\n", 1);
	return (0);
}
