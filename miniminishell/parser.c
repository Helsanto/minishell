/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:05:24 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 14:08:08 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_char_to_token(char *token, char c)
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

static char	**add_token_to_array(char **array, char *token)
{
	int		count = 0;
	char	**new_array;
	int		i;

	if (!token)
		return (array);
	while (array && array[count])
		count++;
	new_array = malloc((count + 2) * sizeof(char *));
	if (!new_array)
	{
		if (array)
		{
			i = 0;
			while (array[i])
				free(array[i++]);
			free(array);
		}
		free(token);
		return (NULL);
	}
	for (int i = 0; i < count; i++)
		new_array[i] = array[i];
	new_array[count] = token;
	new_array[count + 1] = NULL;
	free(array);
	return (new_array);
}


char	**parse_line(char *line)
{
	bool	in_single_quotes = false;
	bool	in_double_quotes = false;
	char	**args = NULL;
	char	*current_token = NULL;
	char	c;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		c = line[i];
		if (c == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;
			continue;
		}
		if (c == '\"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
			continue;
		}
		if ((c == ' ' || c == '\t') && !in_single_quotes && !in_double_quotes)
		{
			if (current_token)
			{
				args = add_token_to_array(args, current_token);
				current_token = NULL;
			}
			i++;
			continue;
		}
		current_token = add_char_to_token(current_token, c);
		if (!current_token)
		{
			if (args)
			{
				j = 0;
				while (args[j])
					free(args[j++]);
				free(args);
			}
			return (NULL);
		}
		i++;
	}
	if (current_token)
		args = add_token_to_array(args, current_token);
	return (args);
}
