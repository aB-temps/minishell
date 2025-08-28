/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:54:18 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/28 18:48:46 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "signals.h"
#include "style.h"
#include "utils.h"
#include <linux/limits.h>

void	get_input(char **env, char **av)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		exit(EXIT_FAILURE);
	input->last_exit_status = 0;
	init_env(env, input);
	setup_signals_interactive();
	if (g_sig == SIGINT)
		handle_sigint(input);
	build_prompt(input);
	input->line = ft_strdup(av[1]);
	if (!input->line)
		exit_parsing(input, input->last_exit_status);
	if (is_valid_input(input->line, input))
	{
		if (parse_input(input) && g_sig != SIGINT)
			start_exec(input);
		clear_vector(&input->v_tokens);
	}
	exit_minishell(input, NULL, 0);
}
