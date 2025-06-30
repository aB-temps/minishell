#ifndef CHECKING_H
# define CHECKING_H

# include <stdbool.h>
# include <sys/types.h>

bool	is_valid_line(char *line);
bool	is_whitespace(char c);
bool	is_operator(char c);
bool	is_quote(char c);
bool	is_d_quote(char c);
bool	is_s_quote(char c);
bool	is_quoted_arg(char *s);

#endif