/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:50:45 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 13:51:14 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_exit(t_cmd *cmd, t_shell_state *state) {
    int exit_code = 0;

    if (cmd->args[1]) {
        exit_code = atoi(cmd->args[1]);
    }
    cleanup_shell(state);
    exit(exit_code);
}

