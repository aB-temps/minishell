/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:47:15 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/29 19:11:27 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "heredoc.h"
#include "signals.h"

static void	fill_heredoc(t_token *token, int *fds, t_input *input)
{
	char	*line;
	char	*tmp;

	tmp = (void *)0;
	while (1)
	{
		line = readline(FG_BLUE"heredoc> "R_ALL);
		if (g_sig == SIGINT || !line || !ft_strcmp(line,
				(char *)token->formatted_content))
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
	if (!line)
		ft_putstr_fd(FG_RED"warning : heredoc exited before EOF\n"R_ALL, STDERR_FILENO);
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
