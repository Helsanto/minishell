/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:19:19 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/06 16:19:22 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:19:19 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/06 16:19:22 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


/* *** Includes *** */
# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* *** Structures *** */
/*
** Structure pour représenter une commande.
** Vous pourrez l’enrichir plus tard : arguments, redirections, etc.
*/
typedef struct s_command
{
    char    **args;    // Tableau d'arguments
    int     argc;      // Nombre d'arguments
    struct s_command *next; // Pour la liste chaînée
}   t_command;

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef struct s_pipeline
{
    t_command   *commands; // Tableau ou liste de commandes
    int         count;      // Nombre de commandes dans le pipeline
    
}   t_pipeline;

/* *** Variables Globales *** */
extern int          g_last_exit_code; // Code de retour de la dernière commande
extern t_env        *g_env_list;      // Liste chaînée des variables d'environnement

/* Builtins */
int builtin_echo(char **args);
int builtin_pwd(char **args);
int builtin_cd(char **args);
int builtin_env(char **args, t_env *env);
int builtin_export(char **args, t_env **env);
int builtin_unset(char **args, t_env **env);
int builtin_exit(char **args);
int execute_builtin(t_command *cmd, t_env **env);

/* Fonctions environnement */
t_env   *init_env(char **environ);
char    *get_env_value(t_env *env, const char *key);
int     set_env_value(t_env **env, const char *key, const char *value);
int     unset_env_value(t_env **env, const char *key);
void    print_env(t_env *env);
void    free_env(t_env *env);

/* Fonctions de commande */
char    *read_input_line(void);
char    **parse_line(char *line);
void    expand_variables(char **args);
void    free_command(t_command *cmd);
t_command *create_command(char **args);
t_command *parse_input_into_commands(const char *input);

/* Fonction de parsing avancée */
t_command *parse_input_into_commands(const char *input);

#endif
