#ifndef DEBUG_H
# define DEBUG_H

# include "exec.h"
# include "parsing.h"
# include "style.h"
# include <stdio.h>

void	print_tab(char **tab);
void	print_input(t_input *input, char *part);
void	print_token_heredoc(t_token token);
void	print_exec(t_exec *exec, const char *stage);

#endif
