/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 05:54:34 by enchevri          #+#    #+#             */
/*   Updated: 2025/09/08 10:55:11 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_token_heredoc(t_token token)
{
	printf("fds[%s%i%s|%s%i%s]\n'", BOLD, ((int *)token.formatted_content)[0],
		RST, BOLD, ((int *)token.formatted_content)[1], RST);
}
