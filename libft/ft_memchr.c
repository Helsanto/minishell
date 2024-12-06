/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:55:31 by msiemon           #+#    #+#             */
/*   Updated: 2024/03/08 13:38:09 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	const unsigned char	*p;
	unsigned char		uc;
	size_t				i;

	p = ptr;
	uc = (unsigned char)value;
	i = 0;
	while (i < num)
	{
		if (p[i] == uc)
		{
			return ((void *)&p[i]);
		}
		i++;
	}
	return (NULL);
}
