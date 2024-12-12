/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:53:07 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/10 11:53:17 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_env_node(char **kv, t_env *env_list)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(kv[0]);
		free(kv[1]);
		free(kv);
		free_env(env_list);
		return (NULL);
	}
	new_node->key = kv[0];
	new_node->value = kv[1];
	new_node->next = env_list;
	free(kv);
	return (new_node);
}

static t_env	*add_env_variable(char *env_var, t_env *env_list)
{
	char	**kv;
	t_env	*new_node;

	kv = split_key_value(env_var);
	if (!kv)
		return (env_list);
	new_node = create_env_node(kv, env_list);
	if (!new_node)
		return (NULL);
	return (new_node);
}

t_env	*init_env(char **environ)
{
	t_env	*env_list;
	int		i;

	env_list = NULL;
	i = 0;
	while (environ[i])
	{
		env_list = add_env_variable(environ[i], env_list);
		if (!env_list)
			return (NULL);
		i++;
	}
	return (env_list);
}

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
