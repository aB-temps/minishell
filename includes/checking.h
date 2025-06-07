#ifndef CHECKING_H
# define CHECKING_H

# include <stdbool.h>

bool	line_is_valid(char *line);
bool	is_whitespace(char c);
bool	is_operator(char c);
bool	is_quote(char c);
bool	is_redir_or_pipe(char c);
bool	is_var_or_assign(char c);
bool	is_valid_arg_char(char c);

#endif