#include "input.h"
#include "parsing.h"
#include "utils.h"

t_env	*init_env(char **env)
{
	t_env	*struct_env;

	struct_env = ft_calloc(1, sizeof(t_env));
	if (!struct_env)
		return ((void *)0);
	struct_env->list = env_array_to_list(env);
	if (!struct_env->list)
	{
		free(struct_env);
		return ((void *)0);
	}
	struct_env->array = ft_tabdup(env);
	if (!struct_env->array)
	{
		ft_lstclear(&struct_env->list, &clear_env_list_elem);
		free(struct_env);
		return ((void *)0);
	}
	return (struct_env);
}

void	init_token(t_token *token)
{
	token->type = -1;
	token->link_to_next = false;
	token->raw_content = (void *)0;
	token->formatted_content = (void *)0;
}