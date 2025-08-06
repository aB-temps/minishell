/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 23:22:39 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/06 01:41:28 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

void	close_and_swap(t_pipe_fds *fds)
{
    ft_close(fds->fd1[0]);
    ft_close(fds->fd1[1]);
    fds->fd1[0] = fds->fd2[0];
    fds->fd1[1] = fds->fd2[1];
    fds->fd2[0] = -1;
    fds->fd2[1] = -1;
}
