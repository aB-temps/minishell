/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 08:55:48 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/29 08:08:29 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

int	safe_close(int fd)
{
	if (fd > -1)
	{
		if (close(fd) < 0)
			return (-1);
		fd = -1;
	}
	return (0);
}
