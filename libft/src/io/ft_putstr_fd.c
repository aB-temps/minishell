/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:10:20 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/23 15:01:19 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	ssize_t	bytes_written;
	size_t	len;

	if (!s)
		return (write(fd, "(null)", 6));
	len = ft_strlen(s);
	bytes_written = write(fd, s, len);
	if (bytes_written == -1 || (size_t)bytes_written != len)
		return (-1);
	return (bytes_written);
}
