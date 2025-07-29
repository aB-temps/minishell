/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_formatting.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:30 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/29 07:55:54 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_FORMATTING_H
# define TEXT_FORMATTING_H

// FOREGROUND COLORS
# define FG_BLACK "\001\033[30m\002"
# define FG_RED "\001\033[31m\002"
# define FG_GREEN "\001\033[32m\002"
# define FG_YELLOW "\001\033[33m\002"
# define FG_BLUE "\001\033[34m\002"
# define FG_MAGENTA "\001\033[35m\002"
# define FG_CYAN "\001\033[36m\002"
# define FG_WHITE "\001\033[97m\002"

// BACKGROUND COLORS
# define BG_BLACK "\001\033[40m\002"
# define BG_RED "\001\033[41m\002"
# define BG_GREEN "\001\033[42m\002"
# define BG_YELLOW "\001\033[43m\002"
# define BG_BLUE "\001\033[44m\002"
# define BG_MAGENTA "\001\033[45m\002"
# define BG_CYAN "\001\033[46m\002"

// FORMAT
# define BOLD "\001\033[1m\002"
# define DIM "\001\033[2m\002"
# define UNDL "\001\033[4m\002"

// RESET
# define R_ALL "\001\033[0m\002"
# define R_BOLD "\001\033[21m\002"
# define R_DIM "\001\033[22m\002"
# define R_UL "\001\033[24m\002"
# define R_FG "\001\033[39m\002"

#endif
