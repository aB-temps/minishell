#include "debug.h"

void	print_input(t_input *input, char *part)
{
	const t_token	*array = (t_token *)input->v_tokens->array;
	ssize_t			i;

	const char *type[11] = {
		"COMMAND",
		"PIPE",
		"REDIR_IN",
		"REDIR_OUT",
		"APPEND",
		"HEREDOC",
		"ARG",
		"S_QUOTES",
		"D_QUOTES",
		"ENV_VAR",
	};
	i = 0;
	printf("================ [DEBUG] ================\n");
	printf("%s => ", part);
	printf("%s%zu tokens%s\n\n", UNDL, input->token_qty, R_ALL);
	while (i < input->token_qty)
	{
		printf("%s[TOKEN %zu]%s\n", BOLD, i + 1, R_ALL);
		printf("Type : %s%s%s\n", BOLD, type[array[i].type], R_ALL);
		printf("Raw Content : '%s%s%s'\n", BOLD, array[i].raw_content, R_ALL);
		if (array[i].type == COMMAND)
			print_tab((char **)array[i].formatted_content);
		else
			printf("Formatted Content : '%s%s%s'\n\n", BOLD,
				(char *)array[i].formatted_content, R_ALL);
		i++;
	}
	printf("=========================================\n\n");
}
