/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:06:14 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 23:30:36 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include "token_formatting.h"
#include "utils.h"

static bool	search_path(char **path, char *cmd, char **cmd_path)
{
	int	i;

	i = 0;
	*cmd_path = NULL;
	while (path[i])
	{
		*cmd_path = ft_strjoin(path[i], "/");
		*cmd_path = str_free_to_join(*cmd_path, cmd);
		if (!*cmd_path)
			return (false);
		if (!access(*cmd_path, X_OK))
			return (true);
		free(*cmd_path);
		++i;
	}
	*cmd_path = NULL;
	return (true);
}

static bool	get_splited_path(t_input *input, char ***splited_path)
{
	char	*path;

	path = get_env_value("PATH", input);
	if (!ft_strlen(path))
	{
		free(path);
		return (false);
	}
	*splited_path = ft_split(path, ':');
	free(path);
	return (true);
}

char	*get_cmd_path(t_input *input, t_exec *exec, char *cmd)
{
	char	**splited_path;
	char	*cmd_path;

	splited_path = NULL;
	if (ft_strchr(cmd, '/') != NULL)
		return (handle_absolute_path(exec, cmd));
	if (!get_splited_path(input, &splited_path))
	{
		exec->return_error = 127;
		return (ft_strdup(cmd));
	}
	if (!splited_path)
		return (NULL);
	if (!search_path(splited_path, cmd, &cmd_path))
		return (free_tab_return_null(splited_path));
	if (!cmd_path)
	{
		exec->return_error = 127;
		free_tab_return_null(splited_path);
		return (ft_strdup(cmd));
	}
	free_tab_return_null(splited_path);
	return (cmd_path);
}
