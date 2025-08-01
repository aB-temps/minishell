/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:22 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/01 04:57:46 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "input.h"
# include "libft.h"
# include <stdio.h>
# include <unistd.h>

char	**ft_tabdup(char **tab);
size_t	ft_tablen(char **tab);
size_t	countocc(char *s, char *to_find);
char	*str_patreplace(char *s, char *old, char *new);
char	*str_patdel(char *s, char *pat);
char	*str_chardel(char *s, char *c);
char	*str_replace(char **from, char *to);
char	*extract_var_key(char *s);
size_t	exp_var_strlen(char *s, t_vector *v_var_array);
void	clear_env_list_elem(void *var);
char	*gen_random_num_sequence(size_t len);
void	clear_hd_filename_elem(t_input *input, const char *temp_dir,
			char *fileid, char *full_path);
void	clear_var_vector(t_vector *v_var_array);
t_list	*lstgetprev(t_list *lst, t_list *elem);
int		safe_close(int fd);
void	unlink_free_tmpfile(char *tmpfile);
void	quoted_arg_len(char quote, size_t *i, char *line);
ssize_t	count_command_args(t_input *input, t_token *array, ssize_t *i);
void	remove_token_if(t_input *input, t_token **array,
			bool (*remove_condition)(t_token *array, ssize_t i));
bool	is_empty_var_token(t_token *array, ssize_t i);
bool	is_redir_object_token(t_token *array, ssize_t i);
void	clear_wds(char *cwd, char *target);
bool	safe_get_cwd(char **wd);

#endif
