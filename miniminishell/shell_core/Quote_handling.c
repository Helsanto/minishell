/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:08:11 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/16 13:08:13 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quotes(char *symbol)
{
	int len;
	int i;

	len = strlen(symbol);
	i = 1;
	
	if (symbol[0] == '\'')
	{
		while (i < len - 1)
		{
			if (symbol[i] == '\n')
				printf("\\n");
			else if (symbol[i] == '\t')
				printf("\\t");
			else if (ft_isprint(symbol[i]))
				printf("%c", symbol[i]);
			else
				printf("\\x%02x", symbol[i]);
			i++;
		}
	}
}
