/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 06:53:15 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/28 17:41:38 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "signals.h"
#include "style.h"

int	main(int ac, char **av, char **env)
{
	if (ac != 2)
		return(printf("%s%sCoucou c'est un minishell de test ou tu rentres l'input en argument%s\n", RED, BOLD, RST));
	// if (isatty(STDIN_FILENO) != 1 || isatty(STDOUT_FILENO) != 1)
	// {
	// 	ft_putstr_fd(YELLOW "minishell: interactive mode only\n" RST,
	// 		STDERR_FILENO);
	// 	exit(2);
	// }
	// welcome();
	rl_event_hook = set_loop;
	get_input(env, av);
	return (0);
}
