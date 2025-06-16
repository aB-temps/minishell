#include "token_formatting.h"

void	replace_env_var(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < input->token_qty)
	{
		if (array[i].type != S_QUOTES && (is_in_string(array[i].raw_content,
					'$') || array[i].type == ENV_VAR))
			format_env_var(input, array, &i);
		else
			i++;
	}
}

static void	handle_extra_quote(char **str)
{
	char	quote;
	char	*temp;

	quote = 0;
	temp = *str;
	if (is_in_string(*str, '\''))
		*str = str_patdel(*str, "'");
	else if (is_in_string(*str, '"'))
		*str = str_patdel(*str, "\"");
	else
		return ;
	free(temp);
}

void	remove_extra_quote(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < input->token_qty)
	{
		if (array[i].type == ENV_VAR)
			handle_extra_quote((char **)&array[i].formatted_content);
		else
			handle_extra_quote(&array[i].raw_content);
		i++;
	}
}

void	format_input(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	i = 0;
	array = (t_token *)input->v_tokens->array;
	replace_env_var(input);
	remove_extra_quote(input);
	while (i < input->token_qty)
	{
		if (array[i].type >= REDIR_IN && array[i].type <= HEREDOC)
			format_redir(input, &i);
		else if (array[i].type == ARG || array[i].type == ENV_VAR
			|| array[i].type == D_QUOTES)
			format_command(input, array, &i);
		else
			i++;
	}
	// input->v_tokens =
}
