/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:14:11 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 14:14:32 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_sig_handler(int signo)
{
    if (signo == SIGINT)
    {
        write(1, "\n> ", 3);
    } 
    else if (signo == SIGQUIT)
    {
        write(1, "\b\b  \b\b", 6);
    }
}

void setup_signal_handlers(void)
{
    signal(SIGINT, ft_sig_handler);
    signal(SIGQUIT, ft_sig_handler);
}
