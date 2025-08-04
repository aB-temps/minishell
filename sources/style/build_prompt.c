/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:56:17 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/05 01:08:05 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "style.h"
#include "token_formatting.h"
#include <linux/limits.h>
#include <unistd.h>

static void	exit_clear_ps(char *ps1, char *ps2, char *ps3, t_input *input)
{
	if (ps1)
	{
		free(ps1);
		ps1 = NULL;
	}
	if (ps2)
	{
		free(ps2);
		ps2 = NULL;
	}
	if (ps3)
	{
		free(ps3);
		ps3 = NULL;
	}
	exit_parsing(input, EXIT_FAILURE);
}

static char	*build_ps1(t_input *input)
{
	char	*ps1;
	char	*username;

	ps1 = (void *)0;
	username = get_env_value("USER", input);
	if (!ft_strlen(username))
		return (username);
	ps1 = ft_strjoin(BLUE, username);
	free(username);
	if (!ps1)
		exit_parsing(input, EXIT_FAILURE);
	ps1 = str_free_to_join(ps1, WHITE " \001→\002 " DIM);
	if (!ps1)
		exit_parsing(input, EXIT_FAILURE);
	return (ps1);
}

static char	*build_ps2(t_input *input, char *ps1)
{
	char	*ps2;
	char	*pwd;

	ps2 = (void *)0;
	pwd = get_env_value("PWD", input);
	ps2 = ft_strjoin(GREEN, pwd);
	safe_free((void **)&pwd);
	if (!ps2)
		exit_clear_ps(ps1, ps2, NULL, input);
	ps2 = str_free_to_join(ps2, R_ALL);
	if (!ps2)
		exit_clear_ps(ps1, ps2, NULL, input);
	return (ps2);
}

static char	*build_ps3(t_input *input, char *ps1, char *ps2)
{
	char	*ps3;
	char	*exit_status;

	ps3 = NULL;
	exit_status = ft_itoa(input->last_exit_status);
	if (!exit_status)
		exit_clear_ps(ps1, ps2, ps3, input);
	if (input->last_exit_status > 0)
		ps3 = ft_strjoin(WHITE " [" RED, exit_status);
	else
		ps3 = ft_strjoin(WHITE " [" GREEN, exit_status);
	safe_free((void **)&exit_status);
	if (!ps3)
		exit_clear_ps(ps1, ps2, ps3, input);
	ps3 = str_free_to_join(ps3, WHITE "]" R_ALL);
	if (!ps3)
		exit_clear_ps(ps1, ps2, ps3, input);
	return (ps3);
}

void	build_prompt(t_input *input)
{
	char	*ps1;
	char	*ps2;
	char	*ps3;

	ps3 = (void *)0;
	ps1 = build_ps1(input);
	ps2 = build_ps2(input, ps1);
	input->prompt = ft_strjoin(ps1, ps2);
	safe_free((void **)&ps1);
	safe_free((void **)&ps2);
	if (!input->prompt)
		exit_parsing(input, EXIT_FAILURE);
	if (input->last_exit_status != -1)
	{
		ps3 = build_ps3(input, ps1, ps2);
		input->prompt = str_free_to_join(input->prompt, ps3);
		safe_free((void **)&ps3);
		if (!input->prompt)
			exit_parsing(input, EXIT_FAILURE);
	}
	input->prompt = str_free_to_join(input->prompt, WHITE "\n$ " R_ALL);
	if (!input->prompt)
		exit_parsing(input, EXIT_FAILURE);
}
