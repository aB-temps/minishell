#include "checking.h"
#include "input.h"

bool	check_syntax_error(t_input *input)
{
	const t_token *array = (t_token *)input->v_tokens->array;
	ssize_t i;

	i = 0;
	if (array[0].type == PIPE)
		return (false);
	while (i < input->token_qty)
	{
		if (i + 1 >= input->token_qty && (array[i].type >= PIPE
				&& array[i].type <= HEREDOC))
			return (false);
		if ((i + 1 < input->token_qty) && (array[i].type >= PIPE
				&& array[i].type <= HEREDOC) && (array[i + 1].type >= PIPE
				&& array[i + 1].type <= HEREDOC))
			return (false);
		i++;
	}
	return (true);
}