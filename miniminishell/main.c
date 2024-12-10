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

/* *** Variables Globales *** */
int g_last_exit_code = 0; // Initialisation à 0
t_env *g_env_list = NULL; // Initialisation à NULL

int main(int argc, char **argv, char **envp)
{
    (void)argc; // Si inutilisé, pour éviter les warnings
    (void)argv; // Si inutilisé, pour éviter les warnings

    char *input;

    /* Initialiser la liste d'environnement globale */
    g_env_list = init_env(envp);
    if (!g_env_list)
    {
        fprintf(stderr, "Failed to initialize environment\n");
        return 1;
    }

    while (1)
    {
        input = readline("myshell> ");
        if (!input)
        {
            printf("exit\n");
            break;
        }

        if (*input)
            add_history(input);

        /* Obtenir une liste de commandes */
        t_command *commands = parse_input_into_commands(input);

        /* Exécution des commandes */
        t_command *tmp = commands;
        while (tmp)
        {
            int ret = execute_builtin(tmp, &g_env_list);
            if (ret == -1 && tmp->args[0])
            {
                printf("Not a builtin: %s\n", tmp->args[0]);
                g_last_exit_code = 1; // Simuler un échec
            }
            else
            {
                g_last_exit_code = ret;
            }
            tmp = tmp->next;
        }

        /* Libération mémoire */
        while (commands)
        {
            t_command *next = commands->next;
            free_command(commands);
            commands = next;
        }
        free(input);
    }

    free_env(g_env_list);
    return 0;
}
