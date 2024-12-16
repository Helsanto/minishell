/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:21:27 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/12 13:21:45 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_char_to_token(char *token, char c)
{
	size_t	len;
	char	*new_token;

	if (!token)
	{
		new_token = malloc(2 * sizeof(char));
		if (!new_token)
			return (NULL);
		new_token[0] = c;
		new_token[1] = '\0';
		return (new_token);
	}
	len = strlen(token);
	new_token = malloc((len + 2) * sizeof(char));
	if (!new_token)
	{
		free(token);
		return (NULL);
	}
	strcpy(new_token, token);
	new_token[len] = c;
	new_token[len + 1] = '\0';
	free(token);
	return (new_token);
}

static void	free_array_and_token(char **array, char *token)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	free(token);
}

static char	**allocate_new_array(char **array, int count, char *token)
{
	char	**new_array;

	new_array = malloc((count + 2) * sizeof(char *));
	if (!new_array)
	{
		free_array_and_token(array, token);
		return (NULL);
	}
	return (new_array);
}

char	**add_token_to_array(char **array, char *token)
{
	int		count;
	char	**new_array;
	int		i;

	count = 0;
	if (!token)
		return (array);
	while (array && array[count])
		count++;
	new_array = allocate_new_array(array, count, token);
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[count] = token;
	new_array[count + 1] = NULL;
	free(array);
	return (new_array);
}

int	add_new_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (1);
	}
	new_node->next = *env;
	*env = new_node;
	return (0);
}
