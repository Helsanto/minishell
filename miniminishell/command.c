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

t_command	*create_command(char **args)
{
	t_command	*cmd;
	int			count;
	int			i;

	count = 0;
	if (!args)
		return (NULL);
	while (args[count])
		count++;
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argc = count;
	cmd->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
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
			return (NULL);
		}
		i++;
	}
	cmd->args[count] = NULL;
	return (cmd);
}
void	free_command(t_command *cmd)
{
	int i;

	if (!cmd)
		return;
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free(cmd);
}

t_command *parse_input_into_commands(const char *input)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;

    char **args = parse_line((char *)input); // Parse la ligne en arguments
    if (!args)
    {
        free(cmd);
        return NULL;
    }

    cmd->args = args;
    cmd->argc = 0;
    while (args[cmd->argc])
        cmd->argc++;

    cmd->next = NULL; // Pas de commande suivante dans cette implémentation de base
    return cmd;
}
