#include "debug.h"
#include "input.h"
#include "token_formatting.h"
#include <fcntl.h>

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

void	fill_heredoc(t_token *token, int *fds, t_input *input)
{
	char	*line;

	while (1)
	{
		line = readline("\e[31m\e[1mHEREDOC > \e[0m");
		if (!ft_strncmp(line, (char *)token->formatted_content,
				ft_strlen((char *)token->formatted_content) + ft_strlen(line)))
			break ;
		ft_putendl_fd(line, fds[0]);
	}
	// close(fds[0]);
	// fds[0] = -1;
	// free(token->formatted_content);
	token->raw_content = ft_strjoin("<< ",
			(char *)token->formatted_content);
	if (!token->raw_content)
		exit_minishell(input, EXIT_FAILURE);
	token->formatted_content = fds;
}

void	open_heredoc(t_token *token, t_input *input)
{
	int			*fds;
	const char	*tmpfile = gen_heredoc_filename(input);

	fds = ft_calloc(2, sizeof(int));
	if (!fds)
		exit_minishell(input, EXIT_FAILURE);
	fds[0] = -1;
	fds[1] = -1;
	fds[0] = open(tmpfile, O_WRONLY | O_CREAT, 0644);
	if (fds[0] < 0)
	{
		free((char *)tmpfile);
		free(fds);
		unlink(tmpfile);
		exit_minishell(input, EXIT_FAILURE);
	}
	fds[1] = open(tmpfile, O_RDONLY);
	if (fds[1] < 0)
	{
		free((char *)tmpfile);
		close(fds[0]);
		free(fds);
		unlink(tmpfile);
		exit_minishell(input, EXIT_FAILURE);
	}
	unlink(tmpfile);
	fill_heredoc(token, fds, input);
}

void	handle_heredoc(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	free(gen_heredoc_filename(input));
	while (i < input->token_qty)
	{
		if (array[i].type == HEREDOC)
		{
			open_heredoc(&array[i], input);
		}
		i++;
	}
}
