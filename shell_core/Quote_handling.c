/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-p <fsilva-p@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:09:56 by fsilva-p          #+#    #+#             */
/*   Updated: 2024/12/06 19:21:47 by fsilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void single_quotes(char *symbol)
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
			{
				printf("\\n");
			}
			else if (ft_isprint(symbol[i]))
			{
				printf("%c", symbol[i]);
			}
			else
			{
				printf("\\x%02x", symbol[i]);
			}
			i++;
		}
	}
}

int main()
{
	char test1[] = "'Hello World\n^$%@%$&*%*./,,,'";
	single_quotes(test1);
	printf("\n");
}