#include "input.h"
#include "parsing.h"

// t_input	*init_input(char *prompt, char *line, char **env, int exit_status)
// {
// 	t_input	*input;

// 	input = ft_calloc(1, sizeof(t_input));
// 	if (!input)
// 		return ((void *)0);
// 	input->prompt = prompt;
// 	input->line = line;
// 	input->env = env_array_to_list(env);
// 	if (!input->env)
// 		return ((void *)0);
// 	input->v_tokens = (void *)0;
// 	input->token_qty = 0;
// 	input->last_exit_status = exit_status;
// 	return (input);
// }
void	init_token(t_token *token)
{
	token->type = -1;
	token->link_to_next = false;
	token->raw_content = (void *)0;
	token->formatted_content = (void *)0;
}