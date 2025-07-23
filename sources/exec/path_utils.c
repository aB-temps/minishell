/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:52 by enzo              #+#    #+#             */
/*   Updated: 2025/07/22 18:03:51 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*check_direct_path(char *cmd)
{
	if (ft_strrchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) != 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	else if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*build_and_check_path(char *path, char *cmd)
{
	char	*temp_path;
	char	*cmd_path;

	temp_path = ft_strjoin(path, "/");
	if (!temp_path)
		return (NULL);
	cmd_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	if (!cmd_path)
		return (NULL);
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
}

char	*find_command_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;
	char	*direct_path;

	direct_path = check_direct_path(cmd);
	if (direct_path)
		return (direct_path);
	i = 0;
	while (paths[i])
	{
		cmd_path = build_and_check_path(paths[i], cmd);
		if (cmd_path)
			return (cmd_path);
		i++;
	}
	return (NULL);
}

char	*find_full_command_path(char *cmd, char **env)
{
	char	*path;
	char	**split_path;
	char	*cmd_path;

	if (!cmd || !env)
		return (NULL);
	path = get_path(env);
	if (!path)
		return (NULL);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	cmd_path = find_command_path(cmd, split_path);
	free_tab_return_null(split_path);
	return (cmd_path);
}
