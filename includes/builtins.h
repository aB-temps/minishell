/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:42 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/29 21:52:40 by enchevri         ###   ########lyon.fr   */
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

int		ft_echo(char **args);
int		ft_cd(char **cmd, t_input *input);
int		ft_pwd(void);
int		ft_env(char **env);
void	ft_exit(char **cmd, t_input *input, t_exec *exec);
void	ft_exit(char **cmd, t_input *input, t_exec *exec);
int		ft_export(char **cmd_args, t_input *input);
int		ft_unset(char **cmd_args, t_input *input);
t_list	*find_env_var(char *key, t_list *env);
void	update_env_array(t_input *input);
void	update_env_list(t_input *input);

#endif
