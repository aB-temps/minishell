/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:00:00 by enzo              #+#    #+#             */
/*   Updated: 2025/09/01 23:00:00 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "style.h"
#include "token_formatting.h"

static int	build_export_args(char **to_exp, char *prev_wd, char *new_wd)
{
	to_exp[0] = ft_strdup("export");
	if (!to_exp[0])
		return (EXIT_FAILURE);
	to_exp[1] = ft_strjoin("OLDPWD=", prev_wd);
	if (!to_exp[1])
	{
		free(to_exp[0]);
		return (EXIT_FAILURE);
	}
	to_exp[2] = ft_strjoin("PWD=", new_wd);
	if (!to_exp[2])
	{
		free(to_exp[0]);
		free(to_exp[1]);
		return (EXIT_FAILURE);
	}
	to_exp[3] = NULL;
	return (EXIT_SUCCESS);
}

static int	export_with_cleanup(char **to_exp, char *new_wd,
		t_minishell *minishell)
{
	ft_export(to_exp, minishell);
	clear_wds(new_wd, NULL);
	free_tab_return_int(to_exp, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	export_pwd_in_cd(char *prev_wd, t_minishell *minishell)
{
	char	**to_exp;
	char	*new_wd;
	const char	msg[109] = "cd: error retrieving current directory: getcwd:\
cannot access parent directories: No such file or directory";

	new_wd = getcwd(NULL, PATH_MAX);
	if (!new_wd)
	{
		ft_putendl_fd((char *)msg, STDERR_FILENO);
		new_wd = get_env_value("PWD", minishell->input);
		if (!new_wd)
			return (EXIT_FAILURE);
	}
	to_exp = ft_calloc(4, sizeof(char *));
	if (!to_exp || build_export_args(to_exp, prev_wd, new_wd))
	{
		clear_wds(new_wd, NULL);
		if (to_exp)
			free_tab_return_int(to_exp, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	return (export_with_cleanup(to_exp, new_wd, minishell));
}
