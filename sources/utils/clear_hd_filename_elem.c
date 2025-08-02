/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_hd_filename_elem.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:47:13 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/02 14:05:02 by abetemps         ###   ########.fr       */
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
	exit_parsing(input, EXIT_FAILURE);
}
