/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_heredoc_filename.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:17:30 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/02 14:04:26 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static char	*search_tmpdir(t_input *input)
{
	char	*tmpdir;

	tmpdir = get_env_value("TMPDIR", input);
	if (!tmpdir)
		exit_parsing(input, EXIT_FAILURE);
	if (!ft_strlen(tmpdir))
	{
		free(tmpdir);
		if (access("/tmp", F_OK) == 0)
			tmpdir = ft_strdup("/tmp/");
		else if (access("/var/tmp", F_OK) == 0)
			tmpdir = ft_strdup("/var/tmp/");
		else if (access("/usr/tmp", F_OK) == 0)
			tmpdir = ft_strdup("/usr/tmp/");
		else
			tmpdir = ft_strdup("./");
		if (!tmpdir)
			exit_parsing(input, EXIT_FAILURE);
	}
	return (tmpdir);
}

char	*gen_heredoc_filename(t_input *input)
{
	const char	*tmpdir = search_tmpdir(input);
	const char	*filename_base = "sh-thd-";
	char		*fileid;
	char		*full_path;

	full_path = (void *)0;
	fileid = gen_random_num_sequence(10);
	if (!fileid)
		clear_hd_filename_elem(input, tmpdir, fileid, full_path);
	full_path = str_free_to_join((char *)tmpdir, (char *)filename_base);
	if (!full_path)
		clear_hd_filename_elem(input, (char *)tmpdir, fileid, full_path);
	full_path = str_free_to_join(full_path, fileid);
	free(fileid);
	fileid = (void *)0;
	if (!full_path)
		clear_hd_filename_elem(input, (char *)tmpdir, fileid, full_path);
	if (access(full_path, F_OK) == 0)
	{
		free(full_path);
		gen_heredoc_filename(input);
	}
	return (full_path);
}
