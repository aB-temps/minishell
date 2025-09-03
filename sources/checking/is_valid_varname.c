/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_varname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:07:38 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/03 23:32:07 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checking.h"
#include "text_formatting.h"
#include <stdio.h>

enum e_bool	is_valid_varname(char *s)
{
	size_t	i;

	i = 0;
	if (!(ft_isalpha(s[i]) || s[i] == '_'))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (FALSE);
	}
	++i;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
		{
			ft_putstr_fd(RED "minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(s, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n" RST, STDERR_FILENO);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
