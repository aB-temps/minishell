#include "token_formatting.h"

static void	handle_env_var_expansion(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < input->token_qty)
	{
		if (array[i].type != S_QUOTES && ft_strchr(array[i].raw_content, '$')
			&& ft_strlen(array[i].raw_content) != 1)
			format_env_var(input, array, &i);
		else
			i++;
	}
}

static void	handle_quotes(t_input *input)
{
	t_token	*array;
	char	*temp;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	while (i < input->token_qty)
	{
		temp = array[i].raw_content;
		if (array[i].type == S_QUOTES
			&& !(i - 1 >= 0 && array[i - 1].type == HEREDOC))
		{
			array[i].raw_content = str_patdel(array[i].raw_content, "'");
			free(temp);
		}
		else if (array[i].type == D_QUOTES
			&& !(i - 1 >= 0 && array[i - 1].type == HEREDOC))
		{
			array[i].raw_content = str_patdel(array[i].raw_content, "\"");
			free(temp);
		}
		i++;
	}
}

void	format_tokens(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	i = 0;
	array = (t_token *)input->v_tokens->array;
	handle_quotes(input);
	handle_env_var_expansion(input);
	while (i < input->token_qty)
	{
		if (array[i].type >= REDIR_IN && array[i].type <= HEREDOC)
			format_redir(input, &i);
		else if (array[i].type == ARG || array[i].type == ENV_VAR
			|| array[i].type == D_QUOTES || array[i].type == S_QUOTES)
			format_command(input, array, &i);
		else
			i++;
	}
}
