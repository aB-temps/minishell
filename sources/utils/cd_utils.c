/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 04:56:51 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/26 16:09:39 by enzo             ###   ########.fr       */
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

enum e_bool	init_target_from_arg(char **target, char *arg)
{
	*target = ft_strdup(arg);
	return (*target != NULL);
}

enum e_bool	init_target_from_home(char **target, t_minishell *minishell)
{
	char	*home_value;

	home_value = get_env_value("HOME", minishell->input);
	if (!home_value || !ft_strlen(home_value))
	{
		ft_putstr_fd(RED "cd: HOME not set\n" RST, STDERR_FILENO);
		return (FALSE);
	}
	*target = home_value;
	return (*target != NULL);
}
