/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 05:11:25 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/02 15:04:34 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "input.h"

int	check_if_dir(t_input *input, char *path)
{
	struct stat	*statbuf;
	int			err;

	statbuf = ft_calloc(1, sizeof(struct stat));
	if (!statbuf)
		exit_parsing(input, 1);
	err = stat(path, statbuf);
	if (err == -1)
	{
		free(statbuf);
		return (errno);
	}
	if (S_ISDIR(statbuf->st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(statbuf);
		return (1);
	}
	free(statbuf);
	return (0);
}
