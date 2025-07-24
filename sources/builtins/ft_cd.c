/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:04:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/24 22:37:30 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

void update_all_pwd(char *path, char **env)
{
	
}

void	ft_cd(char **path, char **env)
{
	if (path[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	if (chdir(path[1]) == -1)
	{
		perror(path[1]);
		return ;
	}
	else
	{
		update_all_pwd(path, env);
	}
}
//cd sans arg