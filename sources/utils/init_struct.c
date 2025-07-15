#include "input.h"

void	init_input(t_input *input, char *line, char *prompt, int exit_status)
{
	input->last_exit_status = exit_status;
	input->token_qty = 0;
	input->v_tokens = (void *)0;
	input->line = line;
	input->prompt = prompt;
}
void	init_token(t_token *token)
{
	token->type = -1;
	token->link_to_next = false;
	token->raw_content = (void *)0;
	token->formatted_content = (void *)0;
}