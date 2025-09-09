/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 04:56:51 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/08 12:31:49 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "style.h"
#include "token_formatting.h"

void	clear_wds(char *cwd, char *target)
{
	if (cwd)
	{
		free(cwd);
		cwd = NULL;
	}
	if (target)
	{
		free(target);
		target = NULL;
	}
}

bool	safe_get_cwd(char **wd)
{
	*wd = getcwd(*wd, PATH_MAX);
	if (!(*wd))
	{
		ft_putstr_fd("cd: error getting current directory\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	init_target_from_arg(char **target, char *arg)
{
	*target = ft_strdup(arg);
	return (*target != NULL);
}

bool	init_target_from_home(char **target, t_minishell *minishell)
{
	char	*home_value;

	home_value = get_env_value("HOME", minishell->input);
	if (!home_value || !ft_strlen(home_value))
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		free(home_value);
		return (false);
	}
	*target = home_value;
	return (*target != NULL);
}
