#include "debug.h"
#include "heredoc.h"

void	fill_heredoc(t_token *token, int *fds, t_input *input)
{
	char	*line;
	char	*tmp;

	tmp = (void *)0;
	while (1)
	{
		line = readline("\e[34m\e[1mheredoc > \e[0m");
		if (!line || !ft_strcmp(line, (char *)token->formatted_content))
			break ;
		if (token->link_to_next)
		{
			tmp = line;
			line = substitute_env_var(line, input);
			free(tmp);
		}
		line = str_free_to_join(line, "\n");
		if (!line)
			exit_minishell(input, EXIT_FAILURE);
		ft_putstr_fd(line, fds[0]);
		free(line);
	}
	safe_close(fds[0]);
	free(token->formatted_content);
	token->formatted_content = fds;
}

static void	open_heredoc(int **fds, char *tmpfile, t_input *input)
{
	*fds = ft_calloc(2, sizeof(int));
	if (!*fds)
		exit_minishell(input, EXIT_FAILURE);
	(*fds)[0] = open(tmpfile, O_WRONLY | O_CREAT, 0644);
	if ((*fds)[0] < 0)
	{
		free(*fds);
		unlink_free_tmpfile(tmpfile);
		exit_minishell(input, EXIT_FAILURE);
	}
	(*fds)[1] = open(tmpfile, O_RDONLY);
	if ((*fds)[1] < 0)
	{
		safe_close((*fds)[0]);
		free(*fds);
		unlink_free_tmpfile(tmpfile);
		exit_minishell(input, EXIT_FAILURE);
	}
	unlink_free_tmpfile(tmpfile);
}
void	handle_heredoc(t_input *input)
{
	t_token	*array;
	int		*fds;
	char	*tmpfile;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	fds = (void *)0;
	tmpfile = (void *)0;
	i = 0;
	while (i < input->token_qty)
	{
		if (array[i].type == HEREDOC)
		{
			tmpfile = gen_heredoc_filename(input);
			open_heredoc(&fds, tmpfile, input);
			fill_heredoc(&array[i], fds, input);
		}
		i++;
	}
}
