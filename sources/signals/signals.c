/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:42:03 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/16 20:04:26 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "signals.h"
#include <unistd.h>

volatile sig_atomic_t	g_sig;

void	sigint_interactive_handler(int sig)
{
	rl_replace_line("", 0);
	rl_done = 1;
	g_sig = sig;
}

void	sigint_command_handler(int sig)
{
	rl_replace_line("", 0);
	rl_done = 1;
	g_sig = sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	sigquit_command_handler(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}
