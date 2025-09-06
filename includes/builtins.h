/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzo <enzo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:42 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/06 19:39:11 by enzo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "checking.h"
# include "input.h"
# include "utils.h"
# include <stdio.h>

typedef struct s_exec		t_exec;

typedef struct s_minishell	t_minishell;

struct						s_minishell
{
	t_input					*input;
	t_exec					*exec;
};

int							ft_echo(char **args);
int							ft_cd(char **cmd, t_minishell *minishell);
int							ft_pwd(void);
int							ft_env(char **env);
void						ft_exit(char **cmd, t_minishell *minishell);
int							ft_export(char **cmd_args, t_minishell *minishell);
int							ft_unset(char **cmd_args, t_minishell *minishell);
t_list						*find_env_var(char *key, t_list *env);
void						update_env_array(t_input *input, t_exec *exec);
void						update_env_list(t_input *input, t_exec *exec);

#endif
