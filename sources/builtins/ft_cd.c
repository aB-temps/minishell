/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:04:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/01 04:59:01 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "token_formatting.h"

static int	export_pwd_in_cd(t_input *input, char *prev_wd)
{
	char	**to_exp;
	char	*new_wd;

	new_wd = NULL;
	if (!safe_get_cwd(&new_wd))
		return (EXIT_FAILURE);
	to_exp = ft_calloc(4, sizeof(char *));
	if (!to_exp)
		exit_minishell(input, EXIT_FAILURE);
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
	ft_export(to_exp, input);
	free(new_wd);
	free_tab_return_int(to_exp, EXIT_FAILURE);
	return (0);
}

static void	change_dir(char *cwd, char *target, t_input *input)
{
	if (chdir(target) < 0)
	{
		perror("cd");
		clear_wds(cwd, target);
		return ;
	}
	else
	{
		if (export_pwd_in_cd(input, cwd))
		{
			clear_wds(cwd, target);
			exit_minishell(input, EXIT_FAILURE);
		}
		clear_wds(cwd, target);
	}
}

bool	init_wds(char **cwd, char **target, char **cmd, t_input *input)
{
	*cwd = getcwd(*cwd, PATH_MAX);
	if (!(*cwd))
		return (false);
	if (cmd[1])
	{
		*target = ft_strdup(cmd[1]);
		if (!(*target))
			exit_minishell(input, EXIT_FAILURE);
	}
	else
	{
		*target = get_env_value("HOME", input);
		if (!ft_strlen(*target))
		{
			clear_wds(*cwd, *target);
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (false);
		}
	}
	return (true);
}

int	ft_cd(char **cmd, t_input *input)
{
	char	*cwd;
	char	*target;

	cwd = NULL;
	target = NULL;
	if (ft_tablen(cmd) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!init_wds(&cwd, &target, cmd, input))
		return (EXIT_FAILURE);
	if (!ft_strcmp(target, "-"))
	{
		target = str_replace(&target, get_env_value("OLDPWD", input));
		if (!ft_strlen(target))
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			clear_wds(cwd, target);
			return (EXIT_FAILURE);
		}
	}
	change_dir(cwd, target, input);
	return (EXIT_SUCCESS);
}
