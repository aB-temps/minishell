/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_formatting.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:19 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/31 17:39:59 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_FORMATTING_H
# define TOKEN_FORMATTING_H

# include "parsing.h"
# include "utils.h"

void	format_tokens(t_input *input);
void	format_command(t_input *input, t_token *array, ssize_t *i);
void	format_redir(t_input *input, ssize_t *i);
size_t	countocc(char *s, char *to_find);
char	*str_patreplace(char *s, char *old, char *new);
char	*str_patdel(char *s, char *pat);
char	*get_env_value(char *var_name, t_input *input);
char	*substitute_env_var(char *s, t_input *input);

#endif
