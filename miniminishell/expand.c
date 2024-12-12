/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:22:56 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/10 11:23:05 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_variable(const char **p)
{
	char		*ret;
	const char	*start;
	size_t		var_len;
	const char	*val;

	if (**p == '?')
	{
		ret = get_return_value();
		(*p)++;
	}
	else
	{
		start = *p;
		while (**p && (isalnum((unsigned char)**p) || **p == '_'))
			(*p)++;
		var_len = *p - start;
		ret = strndup(start, var_len);
		if (ret)
		{
			val = get_env_var_value(ret);
			free(ret);
			ret = strdup(val);
		}
	}
	return (ret);
}

static char	*handle_expansion(const char **p, char *new_arg, size_t *len)
{
	char	*expanded;

	(*p)++;
	expanded = expand_variable(p);
	if (!expanded)
		return (NULL);
	new_arg = allocate_and_concat(new_arg, expanded, strlen(expanded), len);
	free(expanded);
	return (new_arg);
}

static char	*handle_regular_char(const char **p, char *new_arg, size_t *len)
{
	new_arg = allocate_and_concat(new_arg, *p, 1, len);
	if (new_arg)
		(*p)++;
	return (new_arg);
}

static char	*expand_one_argument(const char *arg)
{
	const char	*p = arg;
	char		*new_arg;
	size_t		len;

	new_arg = NULL;
	len = 0;
	while (*p)
	{
		if (*p == '$')
		{
			new_arg = handle_expansion(&p, new_arg, &len);
			if (!new_arg)
				return (NULL);
		}
		else
		{
			new_arg = handle_regular_char(&p, new_arg, &len);
			if (!new_arg)
				return (NULL);
		}
	}
	if (!new_arg)
		return (strdup(""));
	return (new_arg);
}

void	expand_variables(char **args)
{
	int			i;
	char		*expanded;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		expanded = expand_one_argument(args[i]);
		if (expanded)
		{
			free(args[i]);
			args[i] = expanded;
		}
		i++;
	}
}
