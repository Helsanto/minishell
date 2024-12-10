/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:53:07 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/10 11:53:17 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** split_key_value:
** Prend une chaîne de type "KEY=VALUE" et la sépare en deux chaînes.
** Retourne un tableau de deux chaînes (key et value) ou NULL en cas d’erreur.
*/
static char **split_key_value(const char *str)
{
    char **res;
    char *equal_pos = strchr(str, '=');
    size_t key_len;

    if (!equal_pos)
        return NULL;
    key_len = equal_pos - str;
    res = malloc(sizeof(char *) * 3);
    if (!res)
        return NULL;
    res[0] = strndup(str, key_len);
    if (!res[0])
    {
        free(res);
        return NULL;
    }
    res[1] = strdup(equal_pos + 1);
    if (!res[1])
    {
        free(res[0]);
        free(res);
        return NULL;
    }
    res[2] = NULL;
    return res;
}

t_env *init_env(char **environ)
{
    t_env *env_list = NULL;
    t_env *new_node;
    int i = 0;
    char **kv;

    while (environ[i])
    {
        kv = split_key_value(environ[i]);
        if (kv)
        {
            new_node = malloc(sizeof(t_env));
            if (!new_node)
            {
                free(kv[0]);
                free(kv[1]);
                free(kv);
                free_env(env_list);
                return NULL;
            }
            new_node->key = kv[0];
            new_node->value = kv[1];
            new_node->next = env_list;
            env_list = new_node;
            free(kv);
        }
        i++;
    }
    return env_list;
}

char *get_env_value(t_env *env, const char *key)
{
    while (env)
    {
        if (strcmp(env->key, key) == 0)
            return env->value;
        env = env->next;
    }
    return NULL;
}

int set_env_value(t_env **env, const char *key, const char *value)
{
    t_env *current = *env;
    // Cherche si la variable existe déjà
    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            // Met à jour la valeur
            char *new_val = strdup(value);
            if (!new_val)
                return 1;
            free(current->value);
            current->value = new_val;
            return 0;
        }
        current = current->next;
    }
    // Sinon, on crée une nouvelle variable
    t_env *new_node = malloc(sizeof(t_env));
    if (!new_node)
        return 1;
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    if (!new_node->key || !new_node->value)
    {
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return 1;
    }
    new_node->next = *env;
    *env = new_node;
    return 0;
}

int unset_env_value(t_env **env, const char *key)
{
    t_env *current = *env;
    t_env *prev = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return 0; // Si la variable n'existe pas, rien à faire
}

void print_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

void free_env(t_env *env)
{
    t_env *tmp;
    while (env)
    {
        tmp = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = tmp;
    }
}

