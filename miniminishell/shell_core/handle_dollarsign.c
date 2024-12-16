/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollarsign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:07:56 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/16 13:07:58 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollarsign(char *symbol, int *i, int len)
{
	char	var_name[128];
	int		j;
	char	*value;

	j = 0;
	(*i)++;
	while (*i < len && (isalnum(symbol[*i]) || symbol[*i] == '_'))
		var_name[j++] = symbol[(*i)++];
	var_name[j] = '\0';
	value = getenv(var_name);
	if (value)
		printf("%s", value);
	(*i)--;
}
