/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:47:15 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/06 19:16:08 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "signals.h"
#include "text_formatting.h"

static void	fill_heredoc(t_token *token, int *fds, t_input *input)
{
	char	*line;
	char	*line1;

	line = (void *)0;
	while (g_sig != SIGINT)
	{
		if (isatty(fileno(stdin)))
			line = readline(BLUE "heredoc> " RST);
		else
		{
			line1 = get_next_line(fileno(stdin));
			line = ft_strtrim(line1, "\n");
			free(line1);
		}
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
		ft_putstr_fd("warning : heredoc exited before EOF\n", STDERR_FILENO);
	if (g_sig == SIGINT)
		safe_close(&fds[1]);
	safe_close(&fds[0]);
	token->formatted_content = ptr_replace(&token->formatted_content, fds);
}

static void	hd_list_heredoc(t_input *input, int fd, int *fds, char *tmpfile)
{
	t_list	*new;
	int		*fd_ptr;

	fd_ptr = malloc(sizeof(int));
	if (!fd_ptr)
	{
		safe_close(&fds[0]);
		safe_close(&fds[1]);
		unlink_free_tmpfile(tmpfile);
		free(fds);
		exit_parsing(input, input->last_exit_status);
	}
	*fd_ptr = fd;
	new = ft_lstnew(fd_ptr);
	if (!new)
	{
		safe_close(&fds[0]);
		safe_close(&fds[1]);
		unlink_free_tmpfile(tmpfile);
		free(fds);
		free(fd_ptr);
		exit_parsing(input, input->last_exit_status);
	}
	ft_lstadd_back(&input->hd_list, new);
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
	hd_list_heredoc(input, (*fds)[1], *fds, tmpfile);
	if ((*fds)[1] < 0)
	{
		safe_close(&(*fds)[0]);
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
