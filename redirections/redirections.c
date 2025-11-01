/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:04:01 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:41:33 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_input(char **exec, t_info *info)
{
	int	fd;

	fd = open(exec[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Minishell: ", 11);
		write(2, exec[1], ft_strlen(exec[1]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		if (errno == ENOENT)
			return (estat(127, info), -1);
		else if (errno == EACCES)
			return (estat(126, info), -1);
		else
			return (estat(1, info), -1);
	}
	info->fd_in_child = fd;
	return (0);
}

int	ft_output(char **exec, t_info *info)
{
	int	fd;

	fd = open(exec[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "Minishell: ", 11);
		write(2, exec[1], ft_strlen(exec[1]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		if (errno == ENOENT)
			return (estat(127, info), -1);
		else if (errno == EACCES)
			return (estat(126, info), -1);
		else
			return (estat(1, info), -1);
	}
	info->fd_out_child = fd;
	return (0);
}

int	ft_append(char **exec, t_info *info)
{
	int	fd;

	fd = open(exec[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		write(2, "Minishell: ", 11);
		write(2, exec[1], ft_strlen(exec[1]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		if (errno == ENOENT)
			return (estat(127, info), -1);
		else if (errno == EACCES)
			return (estat(126, info), -1);
		else
			return (estat(1, info), -1);
	}
	info->fd_out_child = fd;
	return (0);
}
