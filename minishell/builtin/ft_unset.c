/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:53:16 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 13:53:29 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_unset(t_cmd *cmd, t_shell_state *state) {
    int i = 1;

    while (cmd->args[i]) {
        // Supprimer la variable d'environnement
        ft_unsetenv(cmd->args[i], state->envp);
        i++;
    }
}
