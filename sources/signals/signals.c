/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:42:03 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/02 17:38:21 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "signals.h"
#include <unistd.h>

volatile sig_atomic_t	g_sig;

void	sigint_interactive_handler(int sig)
{
	rl_done = 1;
	g_sig = sig;
}

void	sigint_command_handler(int sig)
{
	rl_done = 1;
	g_sig = sig;
}

void	sigquit_command_handler(int sig)
{
	g_sig = sig;
}
