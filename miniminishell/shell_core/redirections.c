/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msiemon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:08:21 by msiemon           #+#    #+#             */
/*   Updated: 2024/12/16 13:08:24 by msiemon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirect_input(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error Opening File\n");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error redirecting input");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_output(const char *filename)
{
	int fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error Opening File\n");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_output_append(const char *filename)
{
	int fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error Opening File\n");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
