/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:42:12 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/27 22:54:49 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

extern int	g_sig;

void		sigint_handler(int sig);
void		setup_signals(void);

#endif