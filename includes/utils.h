/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:22 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/05 21:19:19 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "exec.h"
# include "input.h"
# include "libft.h"
# include <stdio.h>
# include <unistd.h>

char		**ft_tabdup(char **tab);
size_t		ft_tablen(char **tab);
size_t		countocc(char *s, char *to_find);
char		*str_chardel(char *s, char *c);
char		*str_replace(char **from, char *to);
size_t		exp_var_strlen(char *s, t_vector *v_var_array);
void		clear_env_list_elem(void *var);
char		*gen_random_num_sequence(size_t len);
void		clear_hd_filename_elem(t_input *input, const char *temp_dir,
				char *fileid, char *full_path);
void		clear_var_vector(t_vector *v_var_array);
t_list		*lstgetprev(t_list *lst, t_list *elem);
int			safe_close(int fd);
void		unlink_free_tmpfile(char *tmpfile);
void		quoted_arg_len(char quote, size_t *i, char *line);
ssize_t		count_command_args(t_input *input, t_token *array, ssize_t *i);
void		remove_token_if(t_input *input, t_token **array,
				bool (*remove_condition)(t_token *array, ssize_t i));
bool		is_empty_var_token(t_token *array, ssize_t i);
bool		is_redir_object_token(t_token *array, ssize_t i);
void		clear_wds(char *cwd, char *target);
bool		safe_get_cwd(char **wd);
void		*ptr_replace(void **from, void *to);
void		exit_minishell(t_input *input, t_exec *exec, int exit_code);
size_t		count_blocks(t_token *array, ssize_t tkn_qty);
void		close_fd_exec(t_exec *exec);
bool		init_cmd(t_input *input, t_cmd **cmd, ssize_t *i);
// bool	init_block_array(t_block **block, size_t *block_qty, t_input *input);
char		*get_cmd_path(t_input *input, char *cmd_args);
char		*handle_absolute_path(char *cmd);
void		close_and_swap(t_pipe_fds *fds);
void		ft_close(int fd);
void		init_io_fds(t_token *array, t_block block, ssize_t tkn_qty);
void		free_and_close_exec(t_exec **exec);
char		*str_patreplace(char *s, char *old, char *new);
char		*str_patdel(char *s, char *pat);
char		*extract_var_key(char *s);
t_env_var	last_exit_status_to_var(t_input *input);
t_env_var	string_to_var(char *s, t_input *input);
void		clear_var(t_env_var *var);
bool		is_executable_token(t_token *array, ssize_t i);
void		*safe_free(void **ptr);

#endif
