/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:42:12 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/27 19:46:58 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_sig;

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

void		sigint_handler(int sig);
void		setup_signals(void);

#endif