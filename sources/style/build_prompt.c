/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:56:17 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/28 22:23:35 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "style.h"
#include "token_formatting.h"
#include <linux/limits.h>
#include <unistd.h>

char	*build_ps1(t_input *input)
{
	char	*ps1;
	char	*username;

	ps1 = (void *)0;
	username = get_env_value("USER", input);
	if (!ft_strlen(username))
		return (username);
	ps1 = ft_strjoin(FG_BLUE, username);
	free(username);
	if (!ps1)
		exit_minishell(input, EXIT_FAILURE);
	ps1 = str_free_to_join(ps1, FG_WHITE " → " DIM);
	if (!ps1)
		exit_minishell(input, EXIT_FAILURE);
	return (ps1);
}

char	*build_ps2(t_input *input)
{
	char	*ps2;
	char	*pwd;

	ps2 = (void *)0;
	pwd = get_env_value("PWD", input);
	ps2 = ft_strjoin(FG_GREEN, pwd);
	free(pwd);
	if (!ps2)
		exit_minishell(input, EXIT_FAILURE);
	ps2 = str_free_to_join(ps2, R_ALL);
	if (!ps2)
		exit_minishell(input, EXIT_FAILURE);
	return (ps2);
}

char	*build_ps3(t_input *input)
{
	char	*ps3;
	char	*exit_status;

	exit_status = ft_itoa(input->last_exit_status);
	if (!exit_status)
		exit_minishell(input, EXIT_FAILURE);
	if (input->last_exit_status > 0)
		ps3 = ft_strjoin(FG_WHITE " [" FG_RED, exit_status);
	else
		ps3 = ft_strjoin(FG_WHITE " [" FG_GREEN, exit_status);
	free(exit_status);
	if (!ps3)
		exit_minishell(input, EXIT_FAILURE);
	ps3 = str_free_to_join(ps3, FG_WHITE "]" R_ALL);
	if (!ps3)
		exit_minishell(input, EXIT_FAILURE);
	return (ps3);
}

void	build_prompt(t_input *input)
{
	char	*ps1;
	char	*ps2;
	char	*ps3;

	ps3 = (void *)0;
	ps1 = build_ps1(input);
	ps2 = build_ps2(input);
	input->prompt = ft_strjoin(ps1, ps2);
	free(ps1);
	free(ps2);
	if (!input->prompt)
		exit_minishell(input, EXIT_FAILURE);
	if (input->last_exit_status != -1)
	{
		ps3 = build_ps3(input);
		input->prompt = str_free_to_join(input->prompt, ps3);
		free(ps3);
		if (!input->prompt)
			exit_minishell(input, EXIT_FAILURE);
	}
	input->prompt = str_free_to_join(input->prompt, FG_WHITE "\n\001⚡\002 " R_ALL);
	if (!input->prompt)
		exit_minishell(input, EXIT_FAILURE);
}
