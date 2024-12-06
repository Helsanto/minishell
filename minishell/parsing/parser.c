/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:05:24 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 14:08:08 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_cmd *create_command(char *input) {
    t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd) {
        perror("malloc");
        return NULL;
    }
    cmd->args = ft_split(input, ' ');
    cmd->sep = NONE;
    cmd->next = NULL;
    return cmd;
}

int parsing(char *str, t_shell_state *state) {
    t_cmd *current_cmd;
    char **commands;
    int i;

    // Diviser l'entrée par des points-virgules pour obtenir les commandes séparées
    commands = ft_split(str, ';');
    if (!commands) {
        perror("ft_split");
        return FAILURE;
    }

    // Créer la liste chaînée des commandes
    i = 0;
    while (commands[i]) {
        t_cmd *new_cmd = create_command(commands[i]);
        if (!new_cmd) {
            ft_freetab(commands);
            return FAILURE;
        }
        if (i == 0) {
            state->cmd = new_cmd;
        } else {
            current_cmd->next = new_cmd;
        }
        current_cmd = new_cmd;
        i++;
    }
    ft_freetab(commands);
    return SUCCESS;
}

void cleanup_commands(t_cmd *cmd) {
    t_cmd *tmp;
    while (cmd) {
        tmp = cmd;
        cmd = cmd->next;
        ft_freetab(tmp->args);
        free(tmp);
    }
}

// Fonction utilitaire pour diviser une chaîne en tokens
typedef struct s_tokenizer {
    char **tokens;
    int count;
} t_tokenizer;

char **ft_split(char const *s, char c);
void ft_freetab(char **tab);
