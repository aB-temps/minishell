/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:42:03 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/29 07:53:32 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "signals.h"
#include <unistd.h>

volatile sig_atomic_t	g_sig;

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
	write(1, "\n", 1);
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}


