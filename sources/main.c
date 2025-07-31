/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:53:15 by enchevri          #+#    #+#             */
/*   Updated: 2025/07/31 04:04:03 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "signals.h"
#include "style.h"
#include <stdio.h>



int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	rl_event_hook = set_loop;
	welcome();
	if (isatty(STDIN_FILENO) != 1)
	{
		ft_putstr_fd("minishell: interactive mode only\n", 2);
		exit(2);
	}
	get_input(env);
	return (0);
}
