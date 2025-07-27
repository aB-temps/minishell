/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_formatting.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:30 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/27 19:43:31 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_FORMATTING_H
# define TEXT_FORMATTING_H

// FOREGROUND COLORS
# define FG_BLACK "\001\e[30m\002"
# define FG_RED "\001\e[31m\002"
# define FG_GREEN "\001\e[32m\002"
# define FG_YELLOW "\001\e[33m\002"
# define FG_BLUE "\001\e[34m\002"
# define FG_MAGENTA "\001\e[35m\002"
# define FG_CYAN "\001\e[36m\002"
# define FG_WHITE "\001\e[97m\002"

// BACKGROUND COLORS
# define BG_BLACK "\001\e[40m\002"
# define BG_RED "\001\e[41m\002"
# define BG_GREEN "\001\e[42m\002"
# define BG_YELLOW "\001\e[43m\002"
# define BG_BLUE "\001\e[44m\002"
# define BG_MAGENTA "\001\e[45m\002"
# define BG_CYAN "\001\e[46m\002"

// FORMAT
# define BOLD "\001\e[1m\002"
# define DIM "\001\e[2m\002"
# define UNDL "\001\e[4m\002"

// RESET
# define R_ALL "\001\e[0m\002"
# define R_BOLD "\001\e[21m\002"
# define R_DIM "\001\e[22m\002"
# define R_UL "\001\e[24m\002"
# define R_FG "\001\e[39m\002"

#endif
