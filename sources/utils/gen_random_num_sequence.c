/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_random_num_sequence.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:48:02 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/01 20:44:03 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

static void	*clean_exit(char *seq, int *fd)
{
	if (seq)
		free(seq);
	if (fd && *fd >= 0)
		safe_close(fd);
	return (NULL);
}

char	*gen_random_num_sequence(size_t len)
{
	char			*seq;
	int				fd;
	unsigned int	buf;
	size_t			i;

	seq = NULL;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (clean_exit(seq, &fd));
	seq = ft_calloc(len + 1, sizeof(char));
	if (!seq)
		return (clean_exit(seq, &fd));
	i = 0;
	while (i < len)
	{
		if (read(fd, &buf, sizeof(buf)) < 0)
			return (clean_exit(seq, &fd));
		seq[i] = (buf % 10) + '0';
		i++;
	}
	seq[i] = '\0';
	close(fd);
	return (seq);
}
