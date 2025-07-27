/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:43 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/27 19:43:44 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKING_H
# define CHECKING_H

# include "input.h"
# include <stdbool.h>
# include <sys/types.h>

bool	is_valid_input(char *line);
bool	is_whitespace(char c);
bool	is_operator(char c);
bool	is_quote(char c);
bool	is_d_quote(char c);
bool	is_s_quote(char c);
bool	is_quoted_arg(char *s);
bool	check_syntax_error(t_input *input);

#endif
