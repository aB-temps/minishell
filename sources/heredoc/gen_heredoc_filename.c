/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_heredoc_filename.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:17:30 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/26 18:17:31 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*search_temp_dir(t_input *input)
{
	char	*temp_dir;

	temp_dir = get_env_value("TMPDIR", input);
	if (!temp_dir)
		exit_minishell(input, EXIT_FAILURE);
	if (!ft_strlen(temp_dir))
	{
		free(temp_dir);
		if (access("/tmp", F_OK) == 0)
			temp_dir = ft_strdup("/tmp/");
		else if (access("/var/tmp", F_OK) == 0)
			temp_dir = ft_strdup("/var/tmp/");
		else if (access("/usr/tmp", F_OK) == 0)
			temp_dir = ft_strdup("/usr/tmp/");
		else
			temp_dir = ft_strdup("./");
		if (!temp_dir)
			exit_minishell(input, EXIT_FAILURE);
	}
	return (temp_dir);
}

char	*gen_heredoc_filename(t_input *input)
{
	const char	*temp_dir = search_temp_dir(input);
	const char	*filename_base = "sh-thd-";
	char		*fileid;
	char		*full_path;

	full_path = (void *)0;
	fileid = gen_random_num_sequence(10);
	if (!fileid)
		clear_hd_filename_elem(input, temp_dir, fileid, full_path);
	full_path = str_free_to_join((char *)temp_dir, (char *)filename_base);
	if (!full_path)
		clear_hd_filename_elem(input, (char *)temp_dir, fileid, full_path);
	full_path = str_free_to_join(full_path, fileid);
	free(fileid);
	fileid = (void *)0;
	if (!full_path)
		clear_hd_filename_elem(input, (char *)temp_dir, fileid, full_path);
	if (access(full_path, F_OK) == 0)
	{
		free(full_path);
		gen_heredoc_filename(input);
	}
	return (full_path);
}
