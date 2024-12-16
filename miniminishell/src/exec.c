/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:08:36 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/16 14:09:07 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_abs_cmd_path(char *path_splitted, char *cmd)
{
	char	*abs_cmd_path;
	char	*tmp;

	tmp = ft_strjoin(path_splitted, "/");
	if (!tmp)
		return (NULL);
	abs_cmd_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!abs_cmd_path)
		return (NULL);
	return (abs_cmd_path);
}

/* Extraire et splitter PATH */
static int	init(char **path_splitted[], t_env *env_list)
{
	char	*path;

	path = get_env_value(env_list, "PATH");
	if (!path)
		return (EXIT_FAILURE);
	*path_splitted = ft_split(path, ':'); // Utiliser ta libft
	if (!*path_splitted)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* Trouver le chemin absolu de la commande */
static char	*get_abs_cmd(char *cmd, t_env *env_list)
{
	char	**path_splitted;
	char	*absolute_cmd_path;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	if (init(&path_splitted, env_list) == EXIT_FAILURE)
		return (NULL);
	i = 0;
	while (path_splitted[i])
	{
		absolute_cmd_path = get_abs_cmd_path(path_splitted[i], cmd);
		if (absolute_cmd_path && access(absolute_cmd_path, F_OK) == 0)
		{
			ft_free_split(path_splitted);
			return (absolute_cmd_path);
		}
		free(absolute_cmd_path);
		i++;
	}
	ft_free_split(path_splitted);
	return (NULL);
}

/* Exécuter la commande avec fork et execve */
static int	execute_cmd(t_command *cmd, char *abs_cmd_path, t_env *env_list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0) // Processus enfant
	{
		char **envp = env_list_to_array(env_list); // Convertir env_list en tableau
		if (execve(abs_cmd_path, cmd->args, envp) == -1)
		{
			perror("execve");
			free(envp);
			exit(errno);
		}
	}
	else // Processus parent
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_last_exit_code = WEXITSTATUS(status);
	}
	return (g_last_exit_code);
}

/* Fonction principale pour exécuter une commande */
int	executor(t_command *cmd, t_env *env_list)
{
	int		exit_status;
	char	*abs_cmd_path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (EXIT_SUCCESS);
	if (execute_builtin(cmd, &env_list) == 0)
		return (g_last_exit_code); // Déjà géré par un builtin
	abs_cmd_path = get_abs_cmd(cmd->args[0], env_list);
	if (!abs_cmd_path)
	{
		dprintf(STDERR_FILENO, "%s: command not found\n", cmd->args[0]);
		return (127);
	}
	exit_status = execute_cmd(cmd, abs_cmd_path, env_list);
	free(abs_cmd_path);
	return (exit_status);
}
