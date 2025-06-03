#include "parsing.h"
#include "style.h"

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
	const t_token *array = (t_token *)input->v_tokens->array;
	ssize_t i;

	i = 0;
	printf("================ [DEBUG] ================\n");
	printf("%s%zu tokens%s\n\n", UNDL, input->token_qty, R_ALL);
	while (i < input->token_qty)
	{
		printf("%s[TOKEN %zu]%s\n", BOLD, i + 1, R_ALL);
		printf("Type : %s%s%s\n", BOLD, type[array[i].type], R_ALL);
		printf("Raw Content : '%s%s%s'\n\n", BOLD, array[i].raw_content, R_ALL);
		i++;
	}
	printf("=========================================\n");
}