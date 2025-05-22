#include "lexing.h"
#include "parsing.h"

void	get_input(char **env)
{
	char	*prompt;
	char	*line;
	t_list	*lexing_lst;

	lexing_lst = NULL;
	prompt = NULL;
	line = NULL;
	while (1)
	{
		prompt = build_prompt(get_line_in_env(env, "USER="));
		if (!prompt)
			exit(EXIT_FAILURE);
		line = readline(prompt);
		if (!line)
			break ;
		else if (line[0])
			add_history(line);
		if (lexing(line, &lexing_lst) == 1)
			break ;
		free(line);
		free(prompt);
		ft_lstclear(&lexing_lst, (*free));
	}
	printf("Exited minishell\n");
}
