/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:45:33 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/12 14:45:54 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_return_value(void)
{
	char	buffer[12];
	char	*ret_str;
	int		len;

	len = snprintf(buffer, sizeof(buffer), "%d", g_last_exit_code);
	if (len < 0)
		return (strdup("0"));
	ret_str = strdup(buffer);
	if (!ret_str)
		return (strdup("0"));
	return (ret_str);
}

const char	*get_env_var_value(const char *var)
{
	return (get_env_value(g_env_list, var));
}

char	*allocate_and_concat(char *new_arg, const char *src,
					size_t len, size_t *offset)
{
	char	*tmp;

	tmp = realloc(new_arg, *offset + len + 1);
	if (!tmp)
	{
		free(new_arg);
		return (NULL);
	}
	new_arg = tmp;
	memcpy(new_arg + *offset, src, len);
	*offset += len;
	new_arg[*offset] = '\0';
	return (new_arg);
}
