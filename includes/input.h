/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:43:35 by abetemps          #+#    #+#             */
/*   Updated: 2025/07/29 07:48:00 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "libft.h"
# include <sys/types.h>

enum						e_token_type
{
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	ARG,
	S_QUOTES,
	D_QUOTES,
	ENV_VAR,
};

typedef struct s_input		t_input;
typedef struct s_token		t_token;
typedef struct s_env		t_env;
typedef struct s_env_var	t_env_var;

struct						s_env_var
{
	char					*key;
	char					*value;
};

struct						s_env
{
	t_list					*list;
	char					**array;
};

struct						s_token
{
	ssize_t					type;
	bool					link_to_next;
	char					*raw_content;
	void					*formatted_content;
	int						_padding;
};

struct						s_input
{
	char					*prompt;
	char					*line;
	t_env					*env;
	t_vector				*v_tokens;
	ssize_t					token_qty;
	int						last_exit_status;
	int						_padding;
};

void						init_env(char **env, t_input *input);

void						init_token(t_token *token);
void						create_token(t_input *input, int type,
								char *raw_content, bool to_link);
void						clear_token(t_vector *tokens);
t_token						dup_token(t_token token);
t_list						*env_array_to_list(char **env);
char						**env_list_to_array(t_list *env);
void						exit_minishell(t_input *input, int exit_code);
void						clear_env_list_elem(void *var);

#endif
