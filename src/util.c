/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:26:31 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/16 14:26:48 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**env_list_to_array(t_env *env_list)
{
	int		i;
	int		count;
	char	**envp;
	t_env	*tmp;

	// Compter le nombre d'éléments dans la liste
	count = 0;
	tmp = env_list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}

	// Allouer le tableau
	envp = malloc((count + 1) * sizeof(char *));
	if (!envp)
		return (NULL);

	// Remplir le tableau avec les clés et valeurs
	i = 0;
	tmp = env_list;
	while (tmp)
	{
		envp[i] = malloc(strlen(tmp->key) + strlen(tmp->value) + 2);
		if (!envp[i])
			return (ft_free_split(envp), NULL);
		sprintf(envp[i], "%s=%s", tmp->key, tmp->value);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
