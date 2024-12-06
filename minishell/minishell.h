/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:08:09 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/05 13:08:13 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE 1

# define NONE -1
# define PIPE 0
# define RIGHT 1
# define LEFT 2
# define D_RIGHT 3

typedef struct s_cmd
{
    char            **args;
    int             sep;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_shell_state
{
    t_cmd   *cmd;
    char    **envp;
    int     status;
}   t_shell_state;

// Initialization
void    init_shell(t_shell_state *state, char **envp);
void    cleanup_shell(t_shell_state *state);
void	ft_setenv(char *name, char **envp);


// Parsing
int     parsing(char *str, t_shell_state *state);
char    **ft_split(char const *s, char c);
void    ft_freetab(char **tab);

// Execution
void    execute_command(t_shell_state *state);
int     is_builtin(char *cmd);
void    execute_builtin(t_cmd *cmd, t_shell_state *state);

// Builtins
void    ft_cd(t_cmd *cmd, t_shell_state *state);
void    ft_echo(t_cmd *cmd, t_shell_state *state);
void    ft_env(t_cmd *cmd, t_shell_state *state);
void    ft_exit(t_cmd *cmd, t_shell_state *state);
void    ft_export(t_cmd *cmd, t_shell_state *state);
void    ft_pwd(t_cmd *cmd, t_shell_state *state);
void    ft_unset(t_cmd *cmd, t_shell_state *state);

// Utilities
char    *ft_getenv(char *name, char **envp);
void    update_pwd(t_shell_state *state);
void    error_msg(char *cmd, char *msg, int error_code);

// Signal Handling
void    setup_signal_handlers(void);
void    ft_sig_handler(int signo);

#endif
