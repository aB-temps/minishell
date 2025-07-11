#include "checking.h"

bool	is_d_quote(char c)
{
	return (c == '"');
}

bool	is_s_quote(char c)
{
	return (c == '\'');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	is_quoted_arg(char *s)
{
	size_t i;

	i = 0;
	while (s[i] && !is_whitespace(s[i]) && !is_operator(s[i]))
		if (is_quote(s[i++]))
			return (true);
	return (false);
}