/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:30:00 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/06 21:29:14 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "signals.h"

int	set_loop(void)
{
	return (0);
}

void	handle_sigint(t_input *input)
{
	input->last_exit_status = 130;
	g_sig = 0;
}

void	set_sig_for_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals_interactive(void)
{
	signal(SIGINT, sigint_interactive_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_command(void)
{
	signal(SIGINT, sigint_command_handler);
	signal(SIGQUIT, sigquit_command_handler);
}
