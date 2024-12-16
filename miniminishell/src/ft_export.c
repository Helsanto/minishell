/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:25:04 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/12 15:25:14 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_exit_code;

static int	handle_export_no_equal(t_env **env, const char *arg)
{
	if (set_env_value(env, arg, "") != 0)
	{
		fprintf(stderr, "export: allocation error\n");
		g_last_exit_code = 1;
		return (1);
	}
	return (0);
}

static int	handle_export_allocate_vars(const char *arg,
						char *equal_sign, char **var, char **val)
{
	size_t	var_len;

	var_len = equal_sign - arg;
	*var = strndup(arg, var_len);
	*val = strdup(equal_sign + 1);
	if (!(*var) || !(*val))
	{
		free(*var);
		free(*val);
		fprintf(stderr, "export: allocation error\n");
		g_last_exit_code = 1;
		return (1);
	}
	return (0);
}

static int	handle_export_with_equal(t_env **env,
					const char *arg, char *equal_sign)
{
	char	*var;
	char	*val;

	if (handle_export_allocate_vars(arg, equal_sign, &var, &val) != 0)
		return (1);
	if (set_env_value(env, var, val) != 0)
	{
		fprintf(stderr, "export: allocation error\n");
		free(var);
		free(val);
		g_last_exit_code = 1;
		return (1);
	}
	free(var);
	free(val);
	return (0);
}

static int	process_export_argument(t_env **env, const char *arg)
{
	char	*equal_sign;

	equal_sign = strchr(arg, '=');
	if (!equal_sign)
		return (handle_export_no_equal(env, arg));
	return (handle_export_with_equal(env, arg, equal_sign));
}

int	builtin_export(char **args, t_env **env)
{
	int	i;

	if (!args[1])
	{
		print_env(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (process_export_argument(env, args[i]) != 0)
			return (1);
		i++;
	}
	g_last_exit_code = 0;
	return (0);
}
