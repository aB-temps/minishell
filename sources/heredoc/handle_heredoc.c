#include "input.h"
#include "token_formatting.h"

char	*search_temp_dir(t_input *input)
{
	char	*temp_dir;

	temp_dir = get_env_var("TMPDIR", input);
	if (!temp_dir)
	{
		if (access("/tmp", F_OK) == 0)
			temp_dir = ft_strdup("/tmp/");
		else if (access("/var/tmp", F_OK) == 0)
			temp_dir = ft_strdup("/var/tmp/");
		else if (access("/usr/tmp", F_OK) == 0)
			temp_dir = ft_strdup("/usr/tmp/");
		else
			temp_dir = ft_strdup("./");
	}
	else
		temp_dir = ft_strdup(temp_dir);
	if (!temp_dir)
		exit_minishell(input, EXIT_FAILURE);
	return (temp_dir);
}

char	*gen_heredoc_filename(t_input *input)
{
	const char	*temp_dir = search_temp_dir(input);
	const char	*filename_base = "sh-thd-";
	const char	*fileid = gen_random_num_sequence(10);
	char		*full_path;

	full_path = (void *)0;
	if (!fileid)
	{
		free((char *)temp_dir);
		exit_minishell(input, EXIT_FAILURE);
	}
	full_path = str_free_to_join((char *)temp_dir, (char *)filename_base);
	if (!full_path)
	{
		free((char *)temp_dir);
		free((char *)fileid);
		exit_minishell(input, EXIT_FAILURE);
	}
	full_path = str_free_to_join(full_path, (char *)fileid);
	free((char *)fileid);
	if (!full_path)
		exit_minishell(input, EXIT_FAILURE);
	return (full_path);
}

void	handle_heredoc(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	free(gen_heredoc_filename(input));
	// while (i < input->token_qty)
	// {
	// 	if (array[i].type == HEREDOC)
	// 	{
	// 		read_heredoc(&array[i], input);
	// 	}
	// 	i++;
	// }
}
