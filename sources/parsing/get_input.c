#include "exec.h"
#include "debug.h"
#include "libft.h"
#include "parsing.h"
#include "style.h"
#include <linux/limits.h>
#include <unistd.h>

void	get_input(char **env)
{
	int		exit_status;
	t_input	*input;
	char	*line;
	char	*prompt;

	(void)env;
	exit_status = 0;
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
			input = parse_input(line, prompt, exit_status);
		}
		// print_input(input, "BEFORE EXEC");
		if (input)
		{
			exit_status = exec_cmd(input, env);
			clear_vector(input->v_tokens);
			free(input);
		}
		free(prompt);
		free(line);
	}
}
