#include <stdbool.h>

bool	is_redir_or_pipe(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

bool	is_var_or_assign(char c)
{
	return (c == '$' || c == '=');
}

bool	is_operator(char c)
{
	return (is_redir_or_pipe(c) || is_var_or_assign(c));
}
