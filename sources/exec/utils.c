/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:38:16 by enchevri          #+#    #+#             */
/*   Updated: 2025/05/27 18:17:54 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_command_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (ft_strrchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	else if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	error_occured(t_fd *fd, t_data *data, char *error_msg)
{
	if (error_msg != NULL)
		perror(error_msg);
	free_all(data);
	close_all(fd);
	exit(1);
}

void	free_all(t_data *data)
{
	int	i;
	int	j;

	if (data->args)
	{
		i = 0;
		while (data->args[i])
		{
			j = 0;
			while (data->args[i][j])
				free(data->args[i][j++]);
			free(data->args[i++]);
		}
		free(data->args);
	}
	i = 0;
	while (i < data->count_path)
		free(data->split_path[i++]);
	if (data->split_path)
		free(data->split_path);
	if (data->pid_children)
		free(data->pid_children);
}

void	close_all(t_fd *fd)
{
	if (fd->fd1[0] != -1)
		close(fd->fd1[0]);
	if (fd->fd1[1] != -1)
		close(fd->fd1[1]);
	if (fd->fd2[0] != -1)
		close(fd->fd2[0]);
	if (fd->fd2[1] != -1)
		close(fd->fd2[1]);
}
