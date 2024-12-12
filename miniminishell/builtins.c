/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:01:39 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/10 12:01:49 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int			g_last_exit_code;

int	builtin_env(char **args, t_env *env)
{
	(void)args;
	print_env(env);
	return (0);
}

int	builtin_unset(char **args, t_env **env)
{
	int	i;

	if (!args[1])
	{
		printf("unset: no variable specified\n");
		g_last_exit_code = 1;
		return (1);
	}
	i = 1;
	while (args[i])
	{
		unset_env_value(env, args[i]);
		i++;
	}
	g_last_exit_code = 0;
	return (0);
}

int	execute_builtin(t_command *cmd, t_env **env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (strcmp(cmd->args[0], "echo") == 0)
		g_last_exit_code = builtin_echo(cmd->args);
	else if (strcmp(cmd->args[0], "pwd") == 0)
		g_last_exit_code = builtin_pwd(cmd->args);
	else if (strcmp(cmd->args[0], "cd") == 0)
		g_last_exit_code = builtin_cd(cmd->args);
	else if (strcmp(cmd->args[0], "env") == 0)
		g_last_exit_code = builtin_env(cmd->args, *env);
	else if (strcmp(cmd->args[0], "export") == 0)
		g_last_exit_code = builtin_export(cmd->args, env);
	else if (strcmp(cmd->args[0], "unset") == 0)
		g_last_exit_code = builtin_unset(cmd->args, env);
	else if (strcmp(cmd->args[0], "exit") == 0)
		g_last_exit_code = builtin_exit(cmd->args);
	else
		return (-1);
	return (g_last_exit_code);
}
