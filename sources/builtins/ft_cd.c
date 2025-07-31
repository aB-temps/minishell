/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:04:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/31 04:18:48 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "token_formatting.h"

int	export_pwd_in_cd(t_input *input, char *old_wd, char *new_wd)
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
	to_exp[0] = ft_strdup("export");
	to_exp[1] = ft_strjoin("OLDPWD=", old_wd);
	to_exp[2] = ft_strjoin("PWD=", new_wd);
	to_exp[3] = NULL;
	ft_export(to_exp, input);
	free_tab_return_null(to_exp);
	if (new_wd)
		free(new_wd);
	if (old_wd)
		free(old_wd);
	return (1);
}

int	handle_cd_alone(t_input *input, char *old_wd, char *new_wd)
{
	char	*home;

	export_pwd_in_cd(input, old_wd, new_wd);
	home = get_env_value("HOME", input);
	if (chdir(home) == -1)
	{
		if (!home[0])
			ft_putstr_fd("cd: HOME not set\n", 2);
		else
			perror("cd");
		if (home)
			free(home);
		return (2);
	}
	free(home);
	return (0);
}

bool	init_wds(char **new_wd, char **old_wd)
{
	*new_wd = NULL;
	*old_wd = NULL;
	*old_wd = getcwd(*old_wd, PATH_MAX);
	if (!(*old_wd))
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
	char	*old_wd;

	if (!init_wds(&new_wd, &old_wd))
		return (1);
	if (cmd[1] == NULL)
		return (handle_cd_alone(input, old_wd, new_wd));
	else if (cmd[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (2);
	}
	else if (chdir(cmd[1]) == -1)
	{
		perror(cmd[1]);
		return (2);
	}
	export_pwd_in_cd(input, old_wd, new_wd);
	return (0);
}
