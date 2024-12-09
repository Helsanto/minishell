/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DoubleQuotes_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-p <fsilva-p@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:14:28 by fsilva-p          #+#    #+#             */
/*   Updated: 2024/12/09 19:26:18 by fsilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void double_quotes(char *symbol)
{
	int len;
	int i;
	
	len = strlen(symbol);
	i = 1;
	if (symbol[0] == '\"')
	{
		while (i < len - 1)
		{
			if (symbol[i] == '\n')
				printf("\\n");
			else if (symbol[i] == '\t')
				printf("\\t");
			else if (symbol[i] == '$')
				handle_dollarsign(symbol, &i, len);
			else if (ft_isprint(symbol[i]))
				printf("%c", symbol[i]);
			else
				printf("\\x%02x", symbol[i]);
			i++;
		}
	}
}

/*int main()
{
	char *test1 = "\"Hello, $USER, $, $\"";
	double_quotes(test1);
	printf("\n");
}*/