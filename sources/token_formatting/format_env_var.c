#include "token_formatting.h"

static char	*get_raw_var_name(char *s)
{
	char	*raw_var_name;
	size_t	start;
	size_t	end;

	start = 0;
	while (s[start] && s[start] != '$')
		start++;
	end = start + 1;
	while (s[end] && s[end] != '$' && !is_whitespace(s[end])
		&& !is_quote(s[end]) && !is_operator(s[end]))
		end++;
	raw_var_name = ft_strndup(s + start, end - start);
	if (!raw_var_name)
		return ((void *)0);
	return (raw_var_name);
}

static char	*get_var_name(char *s)
{
	size_t	start;
	size_t	end;
	char	*var_name;

	start = 1;
	end = start;
	while (s[end] && !is_quote(s[end]))
		end++;
	var_name = ft_strndup(s + start, end - start);
	if (!var_name)
		return ((void *)0);
	return (var_name);
}

static char	*get_var_value(char *var_name, int exit_status, int *cursor,
		t_input *input)
{
	char	*var_value;

	if (!ft_strncmp(var_name, "?", ft_strlen("?")))
	{
		var_value = ft_itoa(exit_status);
		if (!var_value)
			return ((void *)0);
	}
	else if (!ft_strlen(var_name))
	{
		(*cursor)++;
		return ("$");
	}
	else
		var_value = get_env_var(var_name, input);
	if (!var_value)
		return ("");
	return (var_value);
}

char	*substitute_env_var_occurences(char *s, int *cursor, t_input *input)
{
	char	*ns;
	char	*var_name;
	char	*raw_var_name;
	char	*var_value;

	ns = (void *)0;
	raw_var_name = get_raw_var_name(s);
	if (!raw_var_name)
		return ((void *)0);
	var_name = get_var_name(raw_var_name);
	if (!var_name)
		return ((void *)0);
	var_value = get_var_value(var_name, input->last_exit_status, cursor, input);
	if (!var_value)
		return ((void *)0);
	ns = str_replace(s, raw_var_name, var_value);
	if (!ft_strncmp(var_name, "?", ft_strlen("?")))
		free(var_value);
	free(raw_var_name);
	free(var_name);
	if (!ns)
		return ((void *)0);
	return (ns);
}

void	format_env_var(t_input *input, t_token *array, ssize_t *i)
{
	char	*content;
	char	*new_content;
	int		cursor;

	cursor = 0;
	content = substitute_env_var_occurences(array[*i].raw_content, &cursor,
			input);
	while (content && ft_strchr(content + cursor, '$'))
	{
		new_content = substitute_env_var_occurences(content, &cursor, input);
		free(content);
		content = new_content;
	}
	array[*i].formatted_content = content;
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	array[*i].type = ENV_VAR;
	(*i)++;
}
