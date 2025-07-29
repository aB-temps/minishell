/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_free_tmpfile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:24:32 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/29 08:07:14 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

void	unlink_free_tmpfile(char *tmpfile)
{
	if (tmpfile)
	{
		unlink(tmpfile);
		free(tmpfile);
	}
}
