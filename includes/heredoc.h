#ifndef HEREDOC_H
# define HEREDOC_H

#include "libft.h"
#include "token_formatting.h"
#include "utils.h"
#include <fcntl.h>


void	handle_heredoc(t_input *input);
char	*gen_heredoc_filename(t_input *input);
#endif