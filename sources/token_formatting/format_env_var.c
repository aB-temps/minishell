#include "token_formatting.h"

// UGLY TO REFACTOR

static char	*substitute_env_var_occurences(char *s, size_t *start)
{
	char	*ns;
	char	*var_name;
	char	*var_value;
	size_t	end;

	ns = (void *)0;        // UGLY TO REFACTOR
	var_name = (void *)0;  // UGLY TO REFACTOR
	var_value = (void *)0; // UGLY TO REFACTOR
	end = 0;
	while (s[*start] && s[*start] != '$')
		(*start)++;
	end = *start + 1;
	while (s[end] && (!is_whitespace(s[end]) && !is_quote(s[end])
			&& s[end] != '$' && ft_isalpha(s[end])))
		(end)++;
	var_name = ft_strndup(s + *start, end - *start);
	if (!var_name)
		return ((void *)0);
	var_value = getenv(var_name + 1);
	ns = str_replace(s, var_name, var_value);
	free(var_name);
	if (!ns)
		return ((void *)0);
	return (ns);
}

void	format_env_var(t_input *input, t_token *array, ssize_t *i)
{
	size_t	start;
	char	*content;
	char	*new_content;

	start = 0;
	content = substitute_env_var_occurences(array[*i].raw_content, &start);
	while (content && is_in_string(content, '$'))
	{
		start = 0;
		new_content = substitute_env_var_occurences(content, &start);
		free(content);
		content = new_content;
	}
	array[*i].formatted_content = content;
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	array[*i].type = ENV_VAR;
	(*i)++;
}
