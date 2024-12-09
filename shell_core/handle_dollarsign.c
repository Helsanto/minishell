/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollarsign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsilva-p <fsilva-p@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:16:35 by fsilva-p          #+#    #+#             */
/*   Updated: 2024/12/09 18:49:18 by fsilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void handle_dollarsign(char *symbol, int *i, int len)
{
	const char *user;

	user = getenv("USER");

	if (*i + 1 < len - 1)
	{
		if (symbol[*i + 1] == 'U' && symbol[*i + 2] == 'S' && symbol[*i + 3] == 'E' && symbol[*i + 4] == 'R')
		{
			if (user)
				printf("%s", user);
			else
				printf("User not set");
			*i += 4;
		}
		else
			printf("$");
	}
}