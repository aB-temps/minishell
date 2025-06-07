#include <checking.h>

bool	is_redir_or_pipe(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

bool	is_var(char c)
{
	return (c == '$');
}

bool	is_in_string(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool	is_operator(char c)
{
	return (is_redir_or_pipe(c) || is_var(c));
}
