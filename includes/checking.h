/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:43 by abetemps          #+#    #+#             */
/*   Updated: 2025/09/04 02:00:03 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKING_H
# define CHECKING_H

# include "input.h"
# include <sys/types.h>
# include <unistd.h>

enum e_bool	is_valid_input(char *line, t_input *input);
enum e_bool	is_whitespace(char c);
enum e_bool	is_operator(char c);
enum e_bool	is_quote(char c);
enum e_bool	is_d_quote(char c);
enum e_bool	is_s_quote(char c);
enum e_bool	is_quoted_arg(char *s);
enum e_bool	is_valid_varname(char *s, int *error);
enum e_bool	check_syntax_error(t_input *input);
void		print_syntax_error(t_input *input);

#endif
