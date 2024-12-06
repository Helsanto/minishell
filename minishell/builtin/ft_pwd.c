/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:52:42 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 13:52:46 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pwd(t_cmd *cmd, t_shell_state *state) {
    char *cwd;

    (void)cmd;
    (void)state;
    cwd = getcwd(NULL, 0);
    if (cwd) {
        printf("%s\n", cwd);
        free(cwd);
    } else {
        perror("pwd");
    }
}
