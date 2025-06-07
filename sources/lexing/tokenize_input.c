#include "lexing.h"

void	*tokenize_input(t_input *input, char *line)
{
	size_t	i;
	size_t	line_len;

	i = 0;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (is_operator(line[i]))
			tokenize_operator(input, &i, line, line_len);
		else if (is_valid_arg_char(line[i]))
			tokenize_arg(input, &i, ARG, line);
		else if (is_quote(line[i]))
		{
			if (!tokenize_quote(input, &i, ARG, line))
				return ((void *)0);
		}
		else
			i++;
	}
	return (input);
}
