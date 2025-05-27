/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:21:24 by enchevri          #+#    #+#             */
/*   Updated: 2025/05/27 18:30:52 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	start_exec(t_token *token, char **env)
{
	t_data	data;
	t_fd	fd;
	int		return_value;

	data.env = env;
	return_value = ft_pipex(&data, &fd);
	free_all(&data);
	close_all(&fd);
	return (return_value);
}
