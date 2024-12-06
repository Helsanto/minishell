/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:48:43 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 13:49:03 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(t_cmd *cmd, t_shell_state *state) {
    int n = 0;
    int i = 1;

    (void)state;
    if (cmd->args[1] && strcmp(cmd->args[1], "-n") == 0) {
        n = 1;
        i = 2;
    }
    while (cmd->args[i]) {
        printf("%s", cmd->args[i]);
        if (cmd->args[i + 1])
            printf(" ");
        i++;
    }
    if (!n)
        printf("\n");
}
