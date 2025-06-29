#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include "style.h"
#include <linux/limits.h>
#include <unistd.h>

void	get_input(char **env)
{
	t_input	*input;
	char	*line;
	char	*prompt;


	line = NULL;
	while (1)
	{
		input = NULL;
		prompt = "NULL";
		build_prompt(&prompt);
		line = readline(prompt);
		if (!line)
		{
			free(prompt);
			break ;
		}
		add_history(line);
		if (is_valid_line(line))
		{
			input = parse_input(line, prompt);
		}
		if (input)
		{
			exec_cmd(input, env);
			clear_vector(input->v_tokens);
			free(input);
		}
		free(prompt);
		free(line);
	}
}
