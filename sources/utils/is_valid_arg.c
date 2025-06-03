#include <stdbool.h>

bool	is_valid_arg_char(char c)
{
	return (ft_isalnum(c) || is_path_char(c) || c == '-' || c == '_');
}