/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:22:56 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/10 11:23:05 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

/* *** Variables Globales *** */
extern int          g_last_exit_code;
extern t_env        *g_env_list; // Liste chaînée des variables d'environnement

static char	*get_return_value(void)
{
    // Convertir le code de retour en chaîne de caractères
    char buffer[12]; // Suffisant pour un entier 32 bits
    int len = snprintf(buffer, sizeof(buffer), "%d", g_last_exit_code);
    if (len < 0)
        return strdup("0"); // En cas d'erreur, retourner "0"

    char *ret_str = strdup(buffer);
    if (!ret_str)
        return strdup("0"); // En cas d'erreur d'allocation, retourner "0"

    return ret_str;
}

/*
** get_env_var_value:
** Retourne la valeur de la variable d'environnement `var` si elle existe,
** sinon retourne "" (une chaîne vide).
*/
static const char	*get_env_var_value(const char *var)
{
    return get_env_value(g_env_list, var);
}

/*
** expand_one_argument:
** Prend un argument, cherche des occurrences de $VAR ou $?.
** Construit une nouvelle chaîne avec les expansions.
*/
static char	*expand_one_argument(const char *arg)
{
    char		*new_arg = NULL;
    const char	*p = arg;
    size_t		len = 0;

    while (*p)
    {
        if (*p == '$')
        {
            p++;
            if (*p == '?')
            {
                // Expansion de $?
                char *ret = get_return_value();
                if (!ret)
                    ret = strdup("0"); // Fallback en cas d'erreur

                size_t ret_len = strlen(ret);
                char *tmp = realloc(new_arg, len + ret_len + 1);
                if (!tmp)
                {
                    free(new_arg);
                    free(ret);
                    return NULL;
                }
                new_arg = tmp;
                memcpy(new_arg + len, ret, ret_len);
                len += ret_len;
                new_arg[len] = '\0';
                free(ret);
                p++;
            }
            else if (*p != '\0' && (isalnum((unsigned char)*p) || *p == '_'))
            {
                // On lit le nom de la variable
                const char *start = p;
                while (*p && (isalnum((unsigned char)*p) || *p == '_'))
                    p++;
                size_t var_len = p - start;
                char *var_name = strndup(start, var_len);
                if (!var_name)
                {
                    free(new_arg);
                    return NULL;
                }
                const char *val = get_env_var_value(var_name);
                free(var_name);
                size_t val_len = strlen(val);
                char *tmp = realloc(new_arg, len + val_len + 1);
                if (!tmp)
                {
                    free(new_arg);
                    return NULL;
                }
                new_arg = tmp;
                memcpy(new_arg + len, val, val_len);
                len += val_len;
                new_arg[len] = '\0';
            }
            else
            {
                // $ suivi d'un caractère non valide, on considère juste '$' comme un char normal
                char *tmp = realloc(new_arg, len + 2);
                if (!tmp)
                {
                    free(new_arg);
                    return NULL;
                }
                new_arg = tmp;
                new_arg[len++] = '$';
                new_arg[len] = '\0';
                // On ne fait pas avancer p car le caractère suivant est déjà traité
            }
        }
        else
        {
            // Caractère normal
            char *tmp = realloc(new_arg, len + 2);
            if (!tmp)
            {
                free(new_arg);
                return NULL;
            }
            new_arg = tmp;
            new_arg[len++] = *p;
            new_arg[len] = '\0';
            p++;
        }
    }
    if (!new_arg)
    {
        // Si on n'a jamais alloué new_arg, alors l'argument était vide
        new_arg = strdup("");
    }
    return new_arg;
}

void	expand_variables(char **args)
{
    int i = 0;
    char *expanded;

    if (!args)
        return;
    while (args[i])
    {
        expanded = expand_one_argument(args[i]);
        if (expanded)
        {
            free(args[i]);
            args[i] = expanded;
        }
        i++;
    }
}
