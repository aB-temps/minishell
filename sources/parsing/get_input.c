/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:54:18 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/03 06:27:24 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "signals.h"
#include "style.h"
#include <linux/limits.h>

static void	reset_input(t_input *input)
{
	if (input->prompt)
	{
		free(input->prompt);
		input->prompt = (void *)0;
	}
	if (input->line)
	{
		if (ft_strlen(input->line))
			add_history(input->line);
		free(input->line);
		input->line = (void *)0;
	}
	input->token_qty = 0;
}

void	get_input(char **env)
{
	t_input	*input;
	char	*line;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		exit(EXIT_FAILURE);
	input->last_exit_status = 0;
	init_env(env, input);
	while (1)
	{
		setup_signals_interactive();
		if (g_sig == SIGINT)
			handle_sigint(input);
		build_prompt(input);
		if (isatty(fileno(stdin)))
			input->line = readline(input->prompt);
		else
		{
			line = get_next_line(fileno(stdin));
			input->line = ft_strtrim(line, "\n");
			free(line);
		}
		if (!input->line)
			exit_parsing(input, input->last_exit_status);
		if (is_valid_input(input->line, input))
		{
			if (parse_input(input) && g_sig != SIGINT)
				start_exec(input);
			clear_vector(&input->v_tokens);
		}
		reset_input(input);
	}
}
