/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:53:15 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/16 20:17:26 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "signals.h"
#include "style.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	if (isatty(STDIN_FILENO) != 1)
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
