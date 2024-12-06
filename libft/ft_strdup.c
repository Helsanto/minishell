/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:06:00 by msiemon           #+#    #+#             */
/*   Updated: 2024/03/11 13:16:23 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char		*dup;
	size_t		len;
	size_t		i;
	const char	*temp;

	len = 0;
	temp = s1;
	while (*temp)
	{
		len++;
		temp++;
	}
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (dup == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}
