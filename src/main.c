/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:26:14 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/06 16:26:17 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_exit_code = 0;
t_env	*g_env_list = NULL;

static int	init_shell(char **envp)
{
	print_banner();
	g_env_list = init_env(envp);
	if (!g_env_list)
	{
		fprintf(stderr, "Failed to initialize environment\n");
		return (1);
	}
	return (0);
}

static void	process_commands(t_command *commands)
{
	t_command	*tmp;

	tmp = commands;
	while (tmp)
	{
		// Exécuter la commande intégrée ou externe
		if (execute_builtin(tmp, &g_env_list) == -1)
			g_last_exit_code = executor(tmp, g_env_list);
		tmp = tmp->next;
	}
}

static void	free_commands(t_command *commands)
{
	t_command	*next;

	while (commands)
	{
		next = commands->next;
		free_command(commands);
		commands = next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_command	*commands;

	(void)argc;
	(void)argv;
	if (init_shell(envp) != 0)
		return (1);
	while (1)
	{
		input = readline("myshell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		commands = parse_input_into_commands(input, g_env_list);
		if (commands)
			process_commands(commands);
		free_commands(commands);
		free(input);
	}
	free_env(g_env_list);
	return (0);
}
