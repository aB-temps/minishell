#include "input.h"

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
