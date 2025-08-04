/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:42:03 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/04 23:40:01 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "signals.h"
#include <unistd.h>

volatile sig_atomic_t	g_sig;

int	set_loop(void)
{
	return (0);
}

void	handle_sigint(t_input *input)
{
	input->last_exit_status = 130;
	g_sig = 0;
}

static void	sigint_handler(int sig)
{
	rl_replace_line("", 0);
	rl_done = 1;
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
