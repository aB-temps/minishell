#include "token_formatting.h"

char	*trim_env_var(char *s, int *i)
{
	while (s[*i] && !is_whitespace(s[*i]))
		(*i)++;
	return (ft_strndup(s, *i));
}

void	format_env_var(t_input *input, ssize_t *i)
{
	t_token	*array;
	char	*var;
	char	*content;
	int		j;

	array = (t_token *)input->v_tokens->array;
	j = 0;
	var = trim_env_var(&array[*i].raw_content[1], &j);
	if (!var)
		exit_minishell(input, EXIT_FAILURE);
	array[*i].type = ENV_VAR;
	content = getenv(var);
	if (ft_strlen(content) == 0)
		array[*i].formatted_content = (void *)0;
	array[*i].formatted_content = ft_strjoin(content, &array[*i].raw_content[j
			+ 1]);
	if (!array[*i].formatted_content)
		exit_minishell(input, EXIT_FAILURE);
	(*i)++;
}
