/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:04:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/24 22:51:35 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

void	ft_cd(char **cmd, t_input *input)
{
	char	*new_wd;

	new_wd = NULL;
	if (cmd[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	if (chdir(cmd[1]) == -1)
	{
		perror(cmd[1]);
		return ;
	}
	else
	{
		new_wd = getcwd(new_wd, PATH_MAX);
		ft_export(&new_wd, input);
	}
}
// cd sans arg