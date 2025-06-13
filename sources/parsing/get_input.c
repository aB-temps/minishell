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

	(void)env;
	line = (void *)0;
	while (1)
	{
		input = (void *)0;
		prompt = (void *)0;
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
		// exec(input)
		free(prompt);
		free(line);
		if (input)
		{
			clear_vector(input->v_tokens);
			free(input);
		}
	}
}
