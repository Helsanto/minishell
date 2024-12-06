/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:47:39 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 13:47:58 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_cmd *cmd, t_shell_state *state) {
    char *path;

    if (!cmd->args[1]) {
        path = ft_getenv("HOME", state->envp);
        if (!path) {
            error_msg("cd", "HOME not set", 1);
            return;
        }
    } else {
        path = cmd->args[1];
    }
    if (chdir(path) != 0) {
        perror("cd");
    } else {
        update_pwd(state);
    }
}
