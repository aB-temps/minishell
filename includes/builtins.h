/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:42 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/29 08:01:43 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "checking.h"
# include "exec.h"
# include "input.h"
# include "utils.h"
# include <linux/limits.h>
# include <stdio.h>

void	ft_echo(char **arguments);
int		ft_cd(char **cmd, t_input *input);
void	ft_pwd(void);
void	ft_env(char **env);
void	ft_exit(char **cmd, t_input *input, t_exec *exec);
int		free_child(t_exec *exec, t_input *input, int error);
void	ft_exit(char **cmd, t_input *input, t_exec *exec);
void	ft_export(char **cmd_args, t_input *input);
void	ft_unset(char **cmd_args, t_input *input);
t_list	*find_env_var(char *key, t_list *env);
void	update_env_array(t_input *input);
void	update_env_list(t_input *input);

#endif
