/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:07:01 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/12 15:07:07 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (update_existing_env_value(current, value));
		current = current->next;
	}
	return (add_new_env_value(env, key, value));
}

int	update_existing_env_value(t_env *current, const char *value)
{
	char	*new_val;

	new_val = strdup(value);
	if (!new_val)
		return (1);
	free(current->value);
	current->value = new_val;
	return (0);
}

int	unset_env_value(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
