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

static bool	handle_quotes_and_spaces(char c, t_quote_state *quote_state,
					char **current_token, char ***args)
{
	if (c == '\'' && !(quote_state->in_double_quotes))
	{
		quote_state->in_single_quotes = !(quote_state->in_single_quotes);
		return (true);
	}
	if (c == '\"' && !(quote_state->in_single_quotes))
	{
		quote_state->in_double_quotes = !(quote_state->in_double_quotes);
		return (true);
	}
	if ((c == ' ' || c == '\t') && !(quote_state->in_single_quotes)
		&& !(quote_state->in_double_quotes))
	{
		if (*current_token)
		{
			*args = add_token_to_array(*args, *current_token);
			*current_token = NULL;
		}
		return (true);
	}
	return (false);
}

static char	*handle_token(char *current_token, char c, char ***args)
{
	int	j;

	current_token = add_char_to_token(current_token, c);
	if (!current_token)
	{
		if (*args)
		{
			j = 0;
			while ((*args)[j])
			{
				free((*args)[j]);
				j++;
			}
			free(*args);
		}
		return (NULL);
	}
	return (current_token);
}

static void	init_parse_state(t_quote_state *quote_state,
				char ***args, char **current_token)
{
	quote_state->in_single_quotes = false;
	quote_state->in_double_quotes = false;
	*args = NULL;
	*current_token = NULL;
}

static bool	process_line_char(char c, t_quote_state *quote_state,
					char **current_token, char ***args)
{
	if (handle_quotes_and_spaces(c, quote_state, current_token, args))
		return (true);
	*current_token = handle_token(*current_token, c, args);
	if (!(*current_token))
		return (false);
	return (true);
}

char	**parse_line(char *line, t_env *env_list)
{
	t_quote_state	quote_state;
	char			**args;
	char			*current_token;
	int				i;

	if (!line)
		return (NULL);
	init_parse_state(&quote_state, &args, &current_token);
	i = 0;
	while (line[i])
	{
		if (!process_line_char(line[i], &quote_state, &current_token, &args))
			return (NULL);
		i++;
	}
	if (current_token)
		args = add_token_to_array(args, current_token);
	expand_variables(args, env_list);
	return (args);
}
