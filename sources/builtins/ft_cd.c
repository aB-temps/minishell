/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:04:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/01 00:27:49 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "token_formatting.h"

int	export_pwd_in_cd(t_input *input, char *actual_wd, char *new_wd)
{
	char	**to_exp;

	new_wd = getcwd(new_wd, PATH_MAX);
	if (!new_wd)
	{
		ft_putstr_fd("minishell: cd: error getting current directory\n",
			STDERR_FILENO);
		return (1);
	}
	to_exp = ft_calloc(4, sizeof(char *));
	if (!to_exp)
		exit_minishell(input, EXIT_FAILURE);
	to_exp[0] = ft_strdup("export");              // malloc de con
	to_exp[1] = ft_strjoin("OLDPWD=", actual_wd); // malloc
	to_exp[2] = ft_strjoin("PWD=", new_wd);       // malloc
	to_exp[3] = NULL;
	ft_export(to_exp, input);
	free_tab_return_null(to_exp);
	if (new_wd)
		free(new_wd);
	if (actual_wd)
		free(actual_wd);
	return (0);
}

int	handle_cd_alone(t_input *input, char *actual_wd, char *new_wd)
{
	char	*home;

	home = get_env_value("HOME", input);
	if (chdir(home) == -1)
	{
		if (!home[0])
			ft_putstr_fd("cd: HOME not set\n", 2);
		else
			perror("cd");
		if (home)
			free(home);
		if (actual_wd)
			free(actual_wd);
		if (new_wd)
			free(new_wd);
		return (1);
	}
	free(home);
	return (0);
}

int	handle_cd_old_pwd(t_input *input)
{
	char	*old_wd;

	old_wd = get_env_value("OLDPWD", input);
	printf("OLDWD= %s\n", old_wd);
	if (chdir(old_wd) == -1)
	{
		if (ft_strlen(old_wd))
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		else
			perror("cd");
		free(old_wd);
		return (1);
	}
	free(old_wd);
	return (0);
}

bool	init_wds(char **new_wd, char **actual_wd)
{
	*new_wd = NULL;
	*actual_wd = NULL;
	*actual_wd = getcwd(*actual_wd, PATH_MAX);
	if (!(*actual_wd))
	{
		ft_putstr_fd("minishell: cd: error getting current directory\n",
			STDERR_FILENO);
		return (false);
	}
	return (true);
}

int	ft_cd(char **cmd, t_input *input)
{
	char	*new_wd;
	char	*actual_wd;

	if (ft_tablen(cmd) >= 3)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!init_wds(&new_wd, &actual_wd))
		return (1);
	if (cmd[1] == NULL)
	{
		if (handle_cd_alone(input, actual_wd, new_wd))
		{
			free(actual_wd);
			return (1);
		}
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		if (handle_cd_old_pwd(input))
		{
			free(actual_wd);
			return (1);
		}
	}
	else if (chdir(cmd[1]) == -1)
	{
		perror(cmd[1]);
		{
			free(actual_wd);
			return (1);
		}
	}
	export_pwd_in_cd(input, actual_wd, new_wd);
	return (0);
}
