/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extrac.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:39:36 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/12 16:39:42 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_key_value_array(void)
{
	char	**res;

	res = malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	res[0] = NULL;
	res[1] = NULL;
	res[2] = NULL;
	return (res);
}

char	*extract_key(const char *str, char *equal_pos)
{
	size_t	key_len;
	char	*key;

	key_len = equal_pos - str;
	key = strndup(str, key_len);
	if (!key)
		return (NULL);
	return (key);
}

char	*extract_value(char *equal_pos)
{
	char	*value;

	value = strdup(equal_pos + 1);
	if (!value)
		return (NULL);
	return (value);
}

char	**split_key_value(const char *str)
{
	char	**res;
	char	*equal_pos;

	equal_pos = strchr(str, '=');
	if (!equal_pos)
		return (NULL);
	res = allocate_key_value_array();
	if (!res)
		return (NULL);
	res[0] = extract_key(str, equal_pos);
	if (!res[0])
	{
		free(res);
		return (NULL);
	}
	res[1] = extract_value(equal_pos);
	if (!res[1])
	{
		free(res[0]);
		free(res);
		return (NULL);
	}
	return (res);
}
