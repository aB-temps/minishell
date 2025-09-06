/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:28:11 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/06 19:39:20 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "text_formatting.h"
#include <limits.h>

int	ft_pwd(void)
{
	const char	msg[109] = "pwd: error retrieving current directory: getcwd:\
	cannot access parent directories: No such file or directory";
	char		*cwd;

	cwd = (void *)0;
	cwd = getcwd(cwd, PATH_MAX);
	if (!cwd)
	{
		ft_putendl_fd((char *)msg, STDERR_FILENO);
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}
