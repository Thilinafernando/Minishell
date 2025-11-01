/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 01:31:10 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:32:20 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_home(t_info *info, char **home)
{
	if (!(*home))
		return (write(2, "Minishell: Home not set\n", 24),
			estat(1, info));
	update_oldpwd(&info->env, info);
	if (chdir((const char *)(*home)) == -1)
	{
		write(2, "Minishell: cd: ", 15);
		write(2, (*home), ft_strlen((*home)));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (free((*home)), estat(1, info));
	}
	update_pwd(&info->env, info);
	return (free(*home), estat(0, info));
}

void	free3(char ***matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free_mat(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_heredocs(int **heredocs)
{
	if (heredocs && *heredocs)
	{
		free(*heredocs);
		*heredocs = NULL;
	}
}

void	free_all(t_info *info)
{
	if (info->fd_in_child > 0)
		close(info->fd_in_child);
	if (info->fd_out_child > 0)
		close(info->fd_out_child);
	info->fd_in_child = -42;
	info->fd_out_child = -42;
	free3(info->exec);
	free_heredocs(&info->heredocs);
	if (info->heredocfd > 0)
		close(info->heredocfd);
	free_mat(info->env);
	close_fd(info->fd_in_out);
	close(0);
	close(1);
	close(2);
}

void	padre(t_info *info)
{
	if (info->fd_in_child > 0)
		close(info->fd_in_child);
	if (info->fd_out_child > 0)
		close(info->fd_out_child);
	info->fd_in_child = -42;
	info->fd_out_child = -42;
	if (info->heredocfd > 0)
		close(info->heredocfd);
	free3(info->exec);
	free_mat(info->env);
	close_fd(info->fd_in_out);
	free_heredocs(&info->heredocs);
}
