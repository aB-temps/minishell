#include <parsing.h>

static bool	is_path_char(char c)
{
	return (c == '.' || c == '/' || c == '~');
}

static bool	is_nonalnum_valid_char(char c)
{
	return (c == '-' || c == '_' || c == '$' || c == '%' || c == '#' || c == '^'
		|| c == '+' || c == '=' || c == ',' || c == '{' || c == '}');
}

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

bool	is_valid_arg_char(char c)
{
	return (ft_isalnum(c) || is_path_char(c) || is_nonalnum_valid_char(c));
}
