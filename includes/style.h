#ifndef STYLE_H
# define STYLE_H

# include "input.h"
# include "text_formatting.h"
# include <linux/limits.h>
# include <stdio.h>
# include <unistd.h>

void	welcome(void);
void	build_prompt(t_input *input);
void	setup_signals(void);

#endif
