/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:04:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/04 01:40:08 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "style.h"
#include "token_formatting.h"

static int	change_dir(char *cwd, char *target, t_minishell *minishell)
{
	if (chdir(target) < 0)
	{
		perror("minishell: cd");
		clear_wds(cwd, target);
		return (EXIT_FAILURE);
	}
	if (export_pwd_in_cd(cwd, minishell))
	{
		clear_wds(cwd, target);
		exit_minishell(minishell->input, minishell->exec, EXIT_FAILURE);
	}
	clear_wds(cwd, target);
	return (EXIT_SUCCESS);
}

static enum e_bool	init_wds(char **cwd, char **target, char **cmd,
		t_minishell *minishell)
{
	*cwd = getcwd(NULL, PATH_MAX);
	if (!(*cwd))
	{
		*cwd = get_env_value("PWD", minishell->input);
		if (!(*cwd))
			exit_minishell(minishell->input, minishell->exec, EXIT_FAILURE);
	}
	if (cmd[1])
	{
		if (!init_target_from_arg(target, cmd[1]))
		{
			clear_wds(*cwd, *target);
			exit_minishell(minishell->input, minishell->exec, EXIT_FAILURE);
		}
	}
	else
	{
		if (!init_target_from_home(target, minishell))
			return (FALSE);
	}
	return (TRUE);
}

static int	handle_oldpwd(char **target, t_minishell *minishell)
{
	*target = str_replace(target, get_env_value("OLDPWD", minishell->input));
	if (!ft_strlen(*target))
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(char **cmd, t_minishell *minishell)
{
	char	*cwd;
	char	*target;

	cwd = NULL;
	target = NULL;
	if (ft_tablen(cmd) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!init_wds(&cwd, &target, cmd, minishell))
	{
		clear_wds(cwd, NULL);
		return (EXIT_FAILURE);
	}
	if (!ft_strcmp(target, "-"))
	{
		if (handle_oldpwd(&target, minishell) == EXIT_FAILURE)
		{
			clear_wds(cwd, target);
			return (EXIT_FAILURE);
		}
	}
	return (change_dir(cwd, target, minishell));
}
