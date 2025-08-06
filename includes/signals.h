/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:42:12 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/06 21:30:58 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

extern volatile sig_atomic_t	g_sig;

void							sigint_interactive_handler(int sig);
void							sigint_command_handler(int sig);
void							sigquit_command_handler(int sig);
int								set_loop(void);
void							handle_sigint(t_input *input);
void							set_sig_for_child(void);
void							setup_signals_interactive(void);
void							setup_signals_command(void);

#endif
