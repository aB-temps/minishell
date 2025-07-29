/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:04:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/29 07:38:08 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "token_formatting.h"

int	ft_cd(char **cmd, t_input *input)
{
	char	*new_wd;
	char	*old_pwd;
	char	**to_exp;
	char	*home;

	to_exp = ft_calloc(4, sizeof(char *));
	if (!to_exp)
		exit_minishell(input, EXIT_FAILURE);
	new_wd = NULL;
	old_pwd = getcwd(new_wd, PATH_MAX);
	to_exp[0] = ft_strdup("export");
	to_exp[1] = ft_strjoin("OLDPWD=", old_pwd);
	if (cmd[1] == NULL)
	{
		home = get_env_value("HOME", input);
		if (!home || chdir(home) == -1)
		{
			if (!home)
				ft_putstr_fd("cd: HOME not set\n", 2);
			else
				perror("cd");
			if (home)
				free(home);
			return (1);
		}
		free(home);
	}
	else if (cmd[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else if (chdir(cmd[1]) == -1)
	{
		perror(cmd[1]);
		return (1);
	}
	new_wd = getcwd(new_wd, PATH_MAX);
	to_exp[2] = ft_strjoin("PWD=", new_wd);
	to_exp[3] = NULL;
	ft_export(to_exp, input);
	free_tab_return_null(to_exp);
	free(new_wd);
	free(old_pwd);
	return (0);
}
