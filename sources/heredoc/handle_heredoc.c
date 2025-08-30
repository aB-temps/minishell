/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:47:15 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/30 16:11:57 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "text_formatting.h"
#include "heredoc.h"
#include "signals.h"

static void	fill_heredoc(t_token *token, int *fds, t_input *input)
{
	char	*line;

	line = (void *)0;
	while (g_sig != SIGINT)
	{
		line = readline(BLUE "heredoc> " RST);
		if (g_sig == SIGINT || !line || !ft_strcmp(line,
				(char *)token->formatted_content))
		{
			if (line)
				free(line);
			break ;
		}
		if (token->link_to_next)
			line = str_replace(&line, substitute_env_var(line, input));
		ft_putendl_fd(line, fds[0]);
		free(line);
	}
	if (!line && g_sig != SIGINT)
		ft_putstr_fd(YELLOW "warning : heredoc exited before EOF\n" RST,
			STDERR_FILENO);
	if (g_sig == SIGINT)
		safe_close(fds[1]);
	safe_close(fds[0]);
	token->formatted_content = ptr_replace(&token->formatted_content, fds);
}

static void	stash_heredoc(t_input *input, int fd, int *fds, char *tmpfile)
{
	t_list	*new;
	int		*fd_ptr;

	fd_ptr = malloc(sizeof(int));
	if (!fd_ptr)
	{
		safe_close(fds[0]);
		safe_close(fds[1]);
		unlink_free_tmpfile(tmpfile);
		free(fds);
		exit_parsing(input, input->last_exit_status);
	}
	*fd_ptr = fd;
	new = ft_lstnew(fd_ptr);
	if (!new)
	{
		safe_close(fds[0]);
		safe_close(fds[1]);
		unlink_free_tmpfile(tmpfile);
		free(fds);
		free(fd_ptr);
		exit_parsing(input, input->last_exit_status);
	}
	ft_lstadd_back(&input->stash, new);
}

static void	open_heredoc(int **fds, char *tmpfile, t_input *input)
{
	*fds = ft_calloc(2, sizeof(int));
	if (!*fds)
	{
		free(tmpfile);
		exit_parsing(input, EXIT_FAILURE);
	}
	(*fds)[0] = open(tmpfile, O_WRONLY | O_CREAT, 0644);
	if ((*fds)[0] < 0)
	{
		free(*fds);
		unlink_free_tmpfile(tmpfile);
		exit_parsing(input, EXIT_FAILURE);
	}
	(*fds)[1] = open(tmpfile, O_RDONLY);
	stash_heredoc(input, (*fds)[1], *fds, tmpfile);
	if ((*fds)[1] < 0)
	{
		safe_close((*fds)[0]);
		free(*fds);
		unlink_free_tmpfile(tmpfile);
		exit_parsing(input, EXIT_FAILURE);
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
			if (g_sig != SIGINT)
				input->last_exit_status = EXIT_SUCCESS;
		}
		i++;
	}
}
