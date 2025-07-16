#include "lexing.h"

void	tokenize_input(t_input *input, char *line)
{
	size_t i;
	size_t line_len;

	i = 0;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (is_whitespace(line[i]))
			i++;
		else if (is_operator(line[i]))
			tokenize_operator(input, &i, line, line_len);
		else if (is_quote(line[i]))
			tokenize_quote(input, &i, line);
		else
			tokenize_word(input, &i, line);
	}
}