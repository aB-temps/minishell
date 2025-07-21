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
		if (!line)
		{
			free(fds);
			exit_minishell(input, EXIT_FAILURE);
		}
		if (!ft_strncmp(line, (char *)token->formatted_content,
				ft_strlen((char *)token->formatted_content) + ft_strlen(line)))
			break ;
		if (!ft_strchr((char *)token->formatted_content, '\'')
				&& !ft_strchr((char *)token->formatted_content, '"'))
		{
			tmp = line;
			line = substitute_env_var(line, input);
			free(tmp);
		}
		line = str_free_to_join(line, "\n");
		if (!line)
			exit_minishell(input, EXIT_FAILURE);
		ft_putstr_fd(line, fds[0]);
		input->line = str_free_to_join(input->line, line);
		free(line);
		if (!input->line)
			exit_minishell(input, EXIT_FAILURE);
	}
	// close(fds[0]); // CLOSE FD{W} ??
	// fds[0] = -1; // CLOSE FD{W} ??
	token->raw_content = str_free_to_join(token->raw_content,
			(char *)token->formatted_content);
	if (!token->raw_content)
		exit_minishell(input, EXIT_FAILURE);
	free(token->formatted_content);
	token->formatted_content = fds;
}

void	open_heredoc(int **fds, char *tmpfile, t_input *input)
{
	(*fds)[0] = open(tmpfile, O_WRONLY | O_CREAT, 0644);
	if ((*fds)[0] < 0)
	{
		free(*fds);
		unlink(tmpfile);
		free(tmpfile);
		exit_minishell(input, EXIT_FAILURE);
	}
	(*fds)[1] = open(tmpfile, O_RDONLY);
	if ((*fds)[1] < 0)
	{
		close((*fds)[0]);
		free(*fds);
		unlink(tmpfile);
		free(tmpfile);
		exit_minishell(input, EXIT_FAILURE);
	}
	unlink(tmpfile);
	free(tmpfile);
}

void	parse_heredoc(t_token *token, t_input *input)
{
	int			*fds;
	const char	*tmpfile = gen_heredoc_filename(input);

	fds = ft_calloc(2, sizeof(int));
	if (!fds)
		exit_minishell(input, EXIT_FAILURE);
	open_heredoc(&fds, (char *)tmpfile, input);
	input->line = str_free_to_join(input->line, "\n");
	if (!input->line)
		exit_minishell(input, EXIT_FAILURE);
	fill_heredoc(token, fds, input);
}

void	handle_heredoc(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < input->token_qty)
	{
		if (array[i].type == HEREDOC)
		{
			parse_heredoc(&array[i], input);
		}
		i++;
	}
}
