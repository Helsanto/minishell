/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:19:25 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 14:19:36 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char **envp) {
    t_shell_state state;
    char *input;
	(void)argc;
	(void)argv;
    // Initialisation de l'état du shell
    init_shell(&state, envp);

    // Boucle principale
    while (1) {
        input = readline("> ");
        if (!input) {
            printf("exit\n");
            break;
        }
        if (*input)
            add_history(input);
        // Parsing de la commande
        if (parsing(input, &state) == 0) {
            execute_command(&state);
        }
        free(input);
    }
    cleanup_shell(&state);
    return 0;
}
