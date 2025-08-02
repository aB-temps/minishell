/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:36 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/02 16:22:30 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "libft.h"
# include "token_formatting.h"
# include "utils.h"
# include <fcntl.h>

void	handle_heredoc(t_input *input);
char	*gen_heredoc_filename(t_input *input);

#endif
