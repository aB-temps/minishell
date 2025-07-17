#ifndef DEBUG_H
# define DEBUG_H

# include "parsing.h"
# include "style.h"
# include <stdio.h>

// Existing functions
void	print_tab(char **tab);
void	print_input(t_input *input, char *part);
void	print_token_heredoc(t_token token);

// New debug functions
void	print_string_array(char **array, const char *array_name);
void	print_all_tokens(t_input *input);
void	print_env_array(char **env);
void	print_int_array(int *array, int size, const char *array_name);
void	debug_print_all_arrays(t_input *input, int *pids, int pid_count);
void	debug_single_token(t_input *input, int token_index);

#endif