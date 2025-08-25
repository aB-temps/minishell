/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:53:15 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/18 19:53:20 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "signals.h"
#include "style.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (isatty(STDIN_FILENO) != 1 || isatty(STDOUT_FILENO) != 1)
	{
		ft_putstr_fd(YELLOW "minishell: interactive mode only\n" RST,
			STDERR_FILENO);
		exit(2);
	}
	welcome();
	rl_event_hook = set_loop;
	get_input(env);
	return (0);
}
