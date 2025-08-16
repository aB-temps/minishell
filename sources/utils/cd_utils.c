/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 04:56:51 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/08 14:10:25 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "style.h"
#include "token_formatting.h"

void	clear_wds(char *cwd, char *target)
{
	if (cwd)
		free(cwd);
	if (target)
		free(target);
}

enum e_bool	safe_get_cwd(char **wd)
{
	*wd = getcwd(*wd, PATH_MAX);
	if (!(*wd))
	{
		ft_putstr_fd(RED "cd: error getting current directory\n" RST,
			STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}
