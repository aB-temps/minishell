#include "input.h"
#include "token_formatting.h"

char	*search_temp_dir(t_input *input)
{
	char	*tempdir;

	tempdir = get_env_var("TMPDIR", input);
	printf("tempdir : %s\n", tempdir);
	// if (!tempdir)
	return (tempdir);
}

// char	*gen_hd_temp_filename(char *num_seq)
// {
// }

void	handle_heredoc(t_input *input)
{
	t_token	*array;
	ssize_t	i;

	array = (t_token *)input->v_tokens->array;
	i = 0;
	search_temp_dir(input);
	// while (i < input->token_qty)
	// {
	// 	if (array[i].type == HEREDOC)
	// 	{
	// 		read_heredoc(&array[i], input);
	// 	}
	// 	i++;
	// }
}
