/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:28:17 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/11 05:20:51 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "exec.h"
#include "input.h"
#include "text_formatting.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_numeric_error(char *arg, t_input *input, t_exec *exec)
{
	input->last_exit_status = 2;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit_minishell(input, exec, input->last_exit_status);
}

void	ft_exit(char **cmd, t_minishell *minishell)
{
	long	nb;
	int		error;

	error = 0;
	if (minishell->exec->block_qty == 1 && isatty(STDERR_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd[1])
		exit_minishell(minishell->input, minishell->exec,
			minishell->input->last_exit_status);
	if (!is_valid_number(cmd[1]))
		print_numeric_error(cmd[1], minishell->input, minishell->exec);
	if (cmd[2])
	{
		minishell->input->last_exit_status = 1;
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return ;
	}
	nb = ft_atoi_long(cmd[1], &error);
	if (error)
		print_numeric_error(cmd[1], minishell->input, minishell->exec);
	minishell->input->last_exit_status = nb % 256;
	exit_minishell(minishell->input, minishell->exec,
		minishell->input->last_exit_status);
}
