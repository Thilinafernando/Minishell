/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:42:24 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:41:43 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_dollar(char **dollar, int fd)
{
	write(fd, (*dollar), ft_strlen((*dollar)));
	write(fd, "\n", 1);
	free((*dollar));
}

void	heredoc_printing_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

int	parent_signal_handler(int *status, t_info *info)
{
	int	exit;

	if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGQUIT)
		{
			write(2, "Quit (core dumped)\n", 19);
			estat(131, info);
			return (-1);
		}
	}
	else if (WIFEXITED(*status))
	{
		exit = WEXITSTATUS(*status);
		if (exit == 130)
		{
			estat(130, info);
			return (-1);
		}
	}
	return (0);
}
