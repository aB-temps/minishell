#include "parsing.h"

void	print_input(t_input *input)
{
	const char *type[11] = {
		"COMMAND",
		"ARG",
		"PIPE",
		"REDIR_IN",
		"REDIR_OUT",
		"APPEND",
		"HEREDOC",
		"ASSIGN",
		"S_QUOTES",
		"D_QUOTES",
		"ENV_VAR",
	};
	ssize_t i;

	i = 0;
	printf("================ [DEBUG] ================\n");
	printf("[TOKENS] quantity -> %zu\n", input->token_qty);
	while (i < input->token_qty)
	{
		printf("Token no %zu : \n", i + 1);
		printf("Type : %s \n", type[((t_token *)input->v_tokens->array)->type]);
		i++;
	}
}