#ifndef CHECKING_H
# define CHECKING_H

# include <stdbool.h>

bool	is_valid_line(char *line);
bool	is_whitespace(char c);
bool	is_operator(char c);
bool	is_quote(char c);
bool	is_redir_or_pipe(char c);
bool	is_var(char c);
bool	is_in_string(char *s, char c);
bool	is_valid_arg_char(char c);

#endif