/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:14:21 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/16 20:04:18 by enzo             ###   ########.fr       */
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
	while (arg[j] && arg[j] != '-')
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
		printf("%s", args[i]);
		if (i < args_qty - 1)
			printf(" ");
		i++;
	}
	if (!n_param)
		printf("\n");
	return (0);
}
