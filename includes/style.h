/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:32 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/06 21:18:30 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STYLE_H
# define STYLE_H

# include "input.h"
# include "text_formatting.h"
# include <linux/limits.h>
# include <stdio.h>
# include <unistd.h>

void	welcome(void);
void	build_prompt(t_input *input);

#endif
