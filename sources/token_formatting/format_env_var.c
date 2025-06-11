#include "token_formatting.h"

char	*trim_env_var(char *s, size_t *start)
{
	char	*ns;
	size_t	end;

	end = 0;
	while (s[*start] != '$')
		(*start)++;
	end = *start + 1;
	while (s[end] && !is_whitespace(s[end]))
		(end)++;
	ns = ft_strndup(s + *start, end - *start);
	return (ns);
}

void	format_env_var(t_input *input, t_token *array, ssize_t *i)
{
	char	*var;
	size_t	start;
	char	*env_var;

	start = 0;
	var = trim_env_var(array[*i].raw_content, &start);
	if (!var)
		exit_minishell(input, EXIT_FAILURE);
	env_var = getenv(var + 1);
	array[*i].formatted_content = str_replace(array[*i].raw_content, var,
			env_var);
	if (!array[*i].formatted_content)
	{
		free(var);
		exit_minishell(input, EXIT_FAILURE);
	}
	free(var);
	array[*i].type = ENV_VAR;
	(*i)++;
}
