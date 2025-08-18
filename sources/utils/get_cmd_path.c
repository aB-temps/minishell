/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:06:14 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/18 04:07:40 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"
#include "token_formatting.h"
#include "utils.h"

static enum e_bool	search_path(char **path, char *cmd, char **cmd_path)
{
	int	i;

	i = 0;
	*cmd_path = NULL;
	while (path[i])
	{
		*cmd_path = ft_strjoin(path[i], "/");
		*cmd_path = str_free_to_join(*cmd_path, cmd);
		if (!*cmd_path)
			return (FALSE);
		if (!access(*cmd_path, X_OK))
			return (TRUE);
		free(*cmd_path);
		++i;
	}
	*cmd_path = NULL;
	return (TRUE);
}

static enum e_bool	get_splited_path(t_input *input, char ***splited_path)
{
	char	*path;

	path = get_env_value("PATH", input);
	if (!ft_strlen(path))
	{
		free(path);
		return (FALSE);
	}
	*splited_path = ft_split(path, ':');
	free(path);
	return (TRUE);
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
		cmd_path = ft_strjoin("./", cmd);
		if (!cmd_path)
			return (NULL);
		return (cmd_path);
	}
	if (!splited_path)
		return (NULL);
	if (!search_path(splited_path, cmd, &cmd_path))
		return (free_tab_return_null(splited_path));
	free_tab_return_null(splited_path);
	return (cmd_path);
}
