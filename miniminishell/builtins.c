/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:01:39 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/10 12:01:49 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* *** Variables Globales *** */
extern int          g_last_exit_code;
extern t_env        *g_env_list; // Liste chaînée des variables d'environnement

int builtin_echo(char **args)
{
    int i = 1;
    int newline = 1;

    if (args[1] && strcmp(args[1], "-n") == 0)
    {
        newline = 0;
        i = 2;
    }

    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
    return 0;
}

int builtin_pwd(char **args)
{
    (void)args;
    char *cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd");
        return 1;
    }
    printf("%s\n", cwd);
    free(cwd);
    return 0;
}

int builtin_cd(char **args)
{
    if (!args[1])
    {
        printf("cd: no argument\n");
        return 1;
    }
    if (chdir(args[1]) != 0)
    {
        perror("cd");
        return 1;
    }
    // Mettre à jour PWD et OLDPWD
    char *new_pwd = getcwd(NULL, 0);
    if (new_pwd)
    {
        set_env_value(&g_env_list, "PWD", new_pwd);
        free(new_pwd);
    }
    return 0;
}

int builtin_env(char **args, t_env *env)
{
    (void)args;
    print_env(env);
    return 0;
}

int builtin_export(char **args, t_env **env)
{
    if (!args[1])
    {
        print_env(*env); // Afficher toutes les variables si aucun argument
        return 0;
    }

    // Parcourir tous les arguments à partir de args[1]
    for (int i = 1; args[i]; i++)
    {
        char *equal_sign = strchr(args[i], '=');
        if (!equal_sign)
        {
            // Si pas de '=', créer la variable avec une valeur vide
            if (set_env_value(env, args[i], "") != 0)
            {
                fprintf(stderr, "export: allocation error\n");
                g_last_exit_code = 1;
                return 1;
            }
        }
        else
        {
            // Séparer VAR et VALUE
            size_t var_len = equal_sign - args[i];
            char *var = strndup(args[i], var_len);
            char *val = strdup(equal_sign + 1);
            if (!var || !val)
            {
                free(var);
                free(val);
                fprintf(stderr, "export: allocation error\n");
                g_last_exit_code = 1;
                return 1;
            }

            if (set_env_value(env, var, val) != 0)
            {
                fprintf(stderr, "export: allocation error\n");
                free(var);
                free(val);
                g_last_exit_code = 1;
                return 1;
            }
            free(var);
            free(val);
        }
    }

    g_last_exit_code = 0;
    return 0;
}

int builtin_unset(char **args, t_env **env)
{
    if (!args[1])
    {
        printf("unset: no variable specified\n");
        g_last_exit_code = 1;
        return 1;
    }

    for (int i = 1; args[i]; i++)
    {
        unset_env_value(env, args[i]);
    }

    g_last_exit_code = 0;
    return 0;
}

int builtin_exit(char **args)
{
    if (args[1])
    {
        // Si un argument est fourni, utiliser comme code de sortie
        int exit_code = atoi(args[1]);
        printf("exit\n");
        exit(exit_code);
    }
    else
    {
        printf("exit\n");
        exit(g_last_exit_code);
    }
    return 0; // Ne sera jamais atteint
}

int execute_builtin(t_command *cmd, t_env **env)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return 1;

    if (strcmp(cmd->args[0], "echo") == 0)
        g_last_exit_code = builtin_echo(cmd->args);
    else if (strcmp(cmd->args[0], "pwd") == 0)
        g_last_exit_code = builtin_pwd(cmd->args);
    else if (strcmp(cmd->args[0], "cd") == 0)
        g_last_exit_code = builtin_cd(cmd->args);
    else if (strcmp(cmd->args[0], "env") == 0)
        g_last_exit_code = builtin_env(cmd->args, *env);
    else if (strcmp(cmd->args[0], "export") == 0)
        g_last_exit_code = builtin_export(cmd->args, env);
    else if (strcmp(cmd->args[0], "unset") == 0)
        g_last_exit_code = builtin_unset(cmd->args, env);
    else if (strcmp(cmd->args[0], "exit") == 0)
        g_last_exit_code = builtin_exit(cmd->args);
    else
        return -1; // Indique que ce n'est pas un builtin.

    return g_last_exit_code;
}
