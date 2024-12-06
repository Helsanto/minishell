/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:51:46 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 13:52:01 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_export(t_cmd *cmd, t_shell_state *state) {
    int i = 1;

    while (cmd->args[i]) {
        // Ajouter ou remplacer la variable d'environnement
        ft_setenv(cmd->args[i], state->envp);
        i++;
    }
}
