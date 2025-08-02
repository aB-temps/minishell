/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 04:56:51 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/02 14:14:16 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "token_formatting.h"

void	clear_wds(char *cwd, char *target)
{
	if (cwd)
		free(cwd);
	if (target)
		free(target);
}

bool	safe_get_cwd(char **wd)
{
	*wd = getcwd(*wd, PATH_MAX);
	if (!(*wd))
	{
		ft_putstr_fd("minishell: cd: error getting current directory\n",
			STDERR_FILENO);
		return (false);
	}
	return (true);
}
