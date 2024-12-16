/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:20:20 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/12 15:20:28 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env		*g_env_list;

int	builtin_cd(char **args)
{
	char	*new_pwd;

	if (!args[1])
	{
		printf("cd: no argument\n");
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		set_env_value(&g_env_list, "PWD", new_pwd);
		free(new_pwd);
	}
	return (0);
}
