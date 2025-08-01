/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:51:52 by enzo              #+#    #+#             */
/*   Updated: 2025/08/01 03:39:00 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
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

static char	*handle_direct_path(char *cmd, int *error)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			*error = 0;
			return (ft_strdup(cmd));
		}
		*error = 126;
		return (NULL);
	}
	*error = 127;
	return (NULL);
}

static char	*find_command_path(char *cmd, char **paths, int *error)
{
	int		i;
	char	*cmd_path;

	if (paths == NULL || ft_strrchr(cmd, '/') != NULL)
		return (handle_direct_path(cmd, error));
	i = 0;
	while (paths[i])
	{
		cmd_path = build_and_check_path(paths[i], cmd);
		if (cmd_path)
		{
			*error = 0;
			return (cmd_path);
		}
		i++;
	}
	*error = 127;
	return (NULL);
}

char	*find_full_command_path(char **cmd, char **env, int *error)
{
	char	*path;
	char	**split_path;
	char	*cmd_path;

	if (!cmd || !env || *cmd[0] == '\0')
	{
		*error = 127;
		return (NULL);
	}
	path = get_path(env);
	split_path = ft_split(path, ':');
	cmd_path = find_command_path(cmd[0], split_path, error);
	if (split_path)
		free_tab_return_null(split_path);
	return (cmd_path);
}
