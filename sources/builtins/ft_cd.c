/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:04:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/30 04:41:30 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "token_formatting.h"

int	handle_cd_alone(t_input *input)
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
		return (0);
	}
	free(home);
	return (0);
}

int	ft_cd(char **cmd, t_input *input)
{
	char	*new_wd;
	char	*old_pwd;
	char	**to_exp;
	int		ret;

	new_wd = NULL;
	old_pwd = NULL;
	old_pwd = getcwd(old_pwd, PATH_MAX);
	if (!old_pwd)
		return (1);
	if (cmd[1] == NULL)
	{
		ret = handle_cd_alone(input);
		if (ret != 0)
		{
			free(old_pwd);
			return (ret);
		}
	}
	else if (cmd[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		free(old_pwd);
		return (1);
	}
	else if (chdir(cmd[1]) == -1)
	{
		perror(cmd[1]);
		free(old_pwd);
		return (1);
	}
	to_exp = ft_calloc(4, sizeof(char *));
	if (!to_exp)
	{
		free(old_pwd);
		exit_minishell(input, EXIT_FAILURE);
	}
	new_wd = getcwd(new_wd, PATH_MAX);
	if (!new_wd)
	{
		free(old_pwd);
		free_tab_return_null(to_exp);
		ft_putstr_fd("minishell: cd: error getting current directory\n",
			STDERR_FILENO);
		return (1);
	}
	to_exp[0] = ft_strdup("export");
	to_exp[1] = ft_strjoin("OLDPWD=", old_pwd);
	to_exp[2] = ft_strjoin("PWD=", new_wd);
	to_exp[3] = NULL;
	ft_export(to_exp, input);
	free_tab_return_null(to_exp);
	free(new_wd);
	free(old_pwd);
	return (0);
}
