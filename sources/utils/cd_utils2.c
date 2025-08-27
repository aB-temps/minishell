/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:00:00 by enzo              #+#    #+#             */
/*   Updated: 2025/08/27 04:32:17 by enzo             ###   ########.fr       */
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

static char	*get_fallback_pwd(t_minishell *minishell)
{
	char	*home_val;
	char	*new_wd;

	home_val = get_env_value("HOME", minishell->input);
	if (!home_val || !ft_strlen(home_val))
		new_wd = ft_strdup("/");
	else
		new_wd = home_val;
	return (new_wd);
}

static int	export_with_cleanup(char **to_exp, char *new_wd,
		t_minishell *minishell)
{
	ft_export(to_exp, minishell);
	clear_wds(new_wd, NULL);
	free_tab_return_int(to_exp, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	export_pwd_in_cd(char *prev_wd, char *target, t_minishell *minishell)
{
	char	**to_exp;
	char	*new_wd;

	(void)target;
	new_wd = getcwd(NULL, PATH_MAX);
	if (!new_wd)
	{
		new_wd = get_fallback_pwd(minishell);
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
