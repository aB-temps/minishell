/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:51:57 by enchevri          #+#    #+#             */
/*   Updated: 2025/08/06 21:51:59 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_input(t_input *input, char *part)
{
	const t_token	*array = (t_token *)input->v_tokens->array;
	ssize_t			i;

	const char *type[11] = {
		"COMMAND",
		"PIPE",
		"REDIR_IN",
		"REDIR_OUT",
		"APPEND",
		"HEREDOC",
		"ARG",
		"S_QUOTES",
		"D_QUOTES",
		"ENV_VAR",
	};
	i = 0;
	printf("================ [DEBUG] ================\n");
	printf("%s => ", part);
	printf("%s%zu tokens%s\n\n", UNDL, input->token_qty, RST);
	while (i < input->token_qty)
	{
		printf("%s[TOKEN %zu]%s\n", BOLD, i + 1, RST);
		if (array[i].type >= 0)
			printf("Type : %s%s%s\n", BOLD, type[array[i].type], RST);
		else
			printf("Type : %s%s%s\n", BOLD, "NULL", RST);
		printf("To link : %s%i%s\n", BOLD, array[i].link_to_next, RST);
		printf("Raw Content : '%s%s%s'\n", BOLD, array[i].raw_content, RST);
		if (array[i].type == COMMAND)
		{
			printf("Formatted Content :\n");
			print_tab((char **)array[i].formatted_content);
		}
		else if (array[i].type == HEREDOC
			&& ft_strlen(array[i].raw_content) > 2)
		{
			printf("Formatted Content :\n");
			// print_token_heredoc(array[i]);
		}
		else
			printf("Formatted Content : '%s%s%s'\n\n", BOLD,
				(char *)array[i].formatted_content, RST);
		i++;
	}
	printf("=========================================\n\n");
}
