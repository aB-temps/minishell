/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:54:18 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/30 15:34:25 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "exec.h"
#include "parsing.h"
#include "signals.h"
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
		free(input->line);
		input->line = (void *)0;
	}
	input->token_qty = 0;
}

_Noreturn void get_input(char **env)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		exit(EXIT_FAILURE);
	init_env(env, input);
	while (1)
	{
		setup_signals();
		if (g_sig == SIGINT)
			handle_sigint(input);
		build_prompt(input);
		input->line = readline(input->prompt);
		if (!input->line)
			exit_minishell(input, input->last_exit_status);
		if (is_valid_input(input->line))
		{
			if (parse_input(input) && g_sig != SIGINT)
				start_exec(input);
			clear_vector(&input->v_tokens);
		}
		if (ft_strlen(input->line))
			add_history(input->line);
		reset_input(input);
	}
}
