#include "token_formatting.h"

static void	replace_env_var(t_input *input)
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

static void	handle_extra_quote(char **str)
{
	const char	*s_quote = ft_strchr(*str, '\'');
	const char	*d_quote = ft_strchr(*str, '"');
	char		*temp;

	temp = (void *)0;
	if (!s_quote && !d_quote)
		return ;
	/*
	if (s_quote && (s_quote < d_quote || !d_quote || *(s_quote
					+ 1) == '\''))
		{
			temp = *str;
			*str = str_patdel(*str, "'");
			}
			if (d_quote && (s_quote > d_quote || !s_quote || *(d_quote
						+ 1) == '"'))
			{
				if (temp)
				free(temp);
				temp = *str;
				*str = str_patdel(*str, "\"");
				}
	*/
	temp = *str;
	if (s_quote)
	{
		*str = str_patdel(*str, "'");
		free(temp);
		temp = *str;
	}
	if (d_quote)
	{
		*str = str_patdel(*str, "\"");
		free(temp);
	}
}

static void	remove_extra_quote(t_input *input)
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

void	format_tokens(t_input *input)
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
			|| array[i].type == D_QUOTES || array[i].type == S_QUOTES)
			format_command(input, array, &i);
		else
			i++;
	}
}
