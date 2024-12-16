/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:23:41 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/12 15:23:48 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int			g_last_exit_code;

int	builtin_exit(char **args)
{
	int	exit_code;

	if (args[1])
	{
		exit_code = atoi(args[1]);
		printf("exit\n");
		exit(exit_code);
	}
	else
	{
		printf("exit\n");
		exit(g_last_exit_code);
	}
	return (0);
}
