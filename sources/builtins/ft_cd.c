/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:04:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/08 14:13:04 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "style.h"
#include "token_formatting.h"

static int	export_pwd_in_cd(char *prev_wd, t_minishell *minishell)
{
	char	**to_exp;
	char	*new_wd;

	new_wd = NULL;
	if (!safe_get_cwd(&new_wd))
		return (EXIT_FAILURE);
	to_exp = ft_calloc(4, sizeof(char *));
	if (!to_exp)
		return (EXIT_FAILURE);
	to_exp[0] = ft_strdup("export");
	if (!to_exp[0])
		return (free_tab_return_int(to_exp, EXIT_FAILURE));
	to_exp[1] = ft_strjoin("OLDPWD=", prev_wd);
	if (!to_exp[1])
		return (free_tab_return_int(to_exp, EXIT_FAILURE));
	to_exp[2] = ft_strjoin("PWD=", new_wd);
	if (!to_exp[2])
		return (free_tab_return_int(to_exp, EXIT_FAILURE));
	to_exp[3] = NULL;
	ft_export(to_exp, minishell);
	free(new_wd);
	free_tab_return_int(to_exp, EXIT_FAILURE);
	return (0);
}

static void	change_dir(char *cwd, char *target, t_minishell *minishell)
{
	if (chdir(target) < 0)
	{
		perror(RED"cd"RST);
		clear_wds(cwd, target);
		return ;
	}
	else
	{
		if (export_pwd_in_cd(cwd, minishell))
		{
			clear_wds(cwd, target);
			exit_minishell(minishell->input, minishell->exec, EXIT_FAILURE);
		}
		clear_wds(cwd, target);
	}
}

static enum e_bool	init_wds(char **cwd, char **target, char **cmd, t_minishell *minishell)
{
	*cwd = getcwd(*cwd, PATH_MAX);
	if (!(*cwd))
		return (FALSE);
	if (cmd[1])
	{
		*target = ft_strdup(cmd[1]);
		if (!(*target))
			exit_minishell(minishell->input, minishell->exec, EXIT_FAILURE);
	}
	else
	{
		*target = get_env_value("HOME", minishell->input);
		if (!ft_strlen(*target))
		{
			clear_wds(*cwd, *target);
			ft_putstr_fd(RED "cd: HOME not set\n" RST, STDERR_FILENO);
			return (FALSE);
		}
	}
	return (TRUE);
}

int	ft_cd(char **cmd, t_minishell *minishell)
{
	char	*cwd;
	char	*target;

	cwd = NULL;
	target = NULL;
	if (ft_tablen(cmd) > 2)
	{
		ft_putstr_fd(RED "cd: too many arguments\n" RST, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!init_wds(&cwd, &target, cmd, minishell))
		return (EXIT_FAILURE);
	if (!ft_strcmp(target, "-"))
	{
		target = str_replace(&target, get_env_value("OLDPWD",
					minishell->input));
		if (!ft_strlen(target))
		{
			ft_putstr_fd(RED "cd: OLDPWD not set\n" RST, STDERR_FILENO);
			clear_wds(cwd, target);
			return (EXIT_FAILURE);
		}
	}
	change_dir(cwd, target, minishell);
	return (EXIT_SUCCESS);
}
