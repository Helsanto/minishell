/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:27:00 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/10 11:27:09 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*initialize_command(int count)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

static int	copy_arguments(t_command *cmd, char **args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		cmd->args[i] = strdup(args[i]);
		if (!cmd->args[i])
		{
			while (--i >= 0)
				free(cmd->args[i]);
			free(cmd->args);
			free(cmd);
			return (1);
		}
		i++;
	}
	cmd->args[count] = NULL;
	return (0);
}

t_command	*create_command(char **args)
{
	t_command	*cmd;
	int			count;

	if (!args)
		return (NULL);
	count = 0;
	while (args[count])
		count++;
	cmd = initialize_command(count);
	if (!cmd)
		return (NULL);
	cmd->argc = count;
	if (copy_arguments(cmd, args, count) != 0)
		return (NULL);
	return (cmd);
}

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free(cmd);
}

t_command	*parse_input_into_commands(const char *input, t_env *env_list)
{
	char		**args;
	t_command	*cmd;
	int			i;

	args = parse_line((char *)input, env_list); // Ajoute env_list ici
	if (!args)
		return (NULL);
	cmd = create_command(args);
	if (!cmd)
	{
		i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
		return (NULL);
	}
	free(args);
	cmd->next = NULL;
	return (cmd);
}
