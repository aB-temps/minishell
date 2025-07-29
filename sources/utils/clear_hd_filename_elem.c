/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_hd_filename_elem.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:13 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/29 08:09:42 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"

void	clear_hd_filename_elem(t_input *input, const char *temp_dir,
		char *fileid, char *full_path)
{
	if (temp_dir)
		free((char *)temp_dir);
	if (fileid)
		free((char *)fileid);
	if (full_path)
		free(full_path);
	exit_minishell(input, EXIT_FAILURE);
}
