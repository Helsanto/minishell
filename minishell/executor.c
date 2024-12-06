/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:58:36 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 13:58:59 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(t_shell_state *state) {
    t_cmd *cmd = state->cmd;

    if (is_builtin(cmd->args[0])) {
        execute_builtin(cmd, state);
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            // Enfant : Exécuter la commande externe
            execve(cmd->args[0], cmd->args, state->envp);
            perror("execve");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Erreur lors de la création du processus enfant
            perror("fork");
        } else {
            // Parent : Attendre la fin de l'enfant
            waitpid(pid, &state->status, 0);
        }
    }
}

int is_builtin(char *cmd) {
    if (strcmp(cmd, "cd") == 0 || strcmp(cmd, "echo") == 0 ||
        strcmp(cmd, "env") == 0 || strcmp(cmd, "exit") == 0 ||
        strcmp(cmd, "export") == 0 || strcmp(cmd, "pwd") == 0 ||
        strcmp(cmd, "unset") == 0) {
        return 1;
    }
    return 0;
}

void execute_builtin(t_cmd *cmd, t_shell_state *state) {
    if (strcmp(cmd->args[0], "cd") == 0) {
        ft_cd(cmd, state);
    } else if (strcmp(cmd->args[0], "echo") == 0) {
        ft_echo(cmd, state);
    } else if (strcmp(cmd->args[0], "env") == 0) {
        ft_env(cmd, state);
    } else if (strcmp(cmd->args[0], "exit") == 0) {
        ft_exit(cmd, state);
    } else if (strcmp(cmd->args[0], "export") == 0) {
        ft_export(cmd, state);
    } else if (strcmp(cmd->args[0], "pwd") == 0) {
        ft_pwd(cmd, state);
    } else if (strcmp(cmd->args[0], "unset") == 0) {
        ft_unset(cmd, state);
    }
}
