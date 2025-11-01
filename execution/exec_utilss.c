/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utilss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:25:37 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/06/03 16:30:57 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_builtin_redirection(char ***matrix, t_info *info, int mat)
{
	if (info->fd_in_child > 0)
	{
		if (dup2(info->fd_in_child, 0) == -1)
		{
			write(2, "Minishell: error dup2\n", 22);
			free_all(info);
			return (0);
		}
		close(info->fd_in_child);
	}
	if (info->fd_out_child > 0)
	{
		if (dup2(info->fd_out_child, 1) == -1)
		{
			write(2, "Minishell: error dup2\n", 22);
			free_all(info);
			return (0);
		}
		close(info->fd_out_child);
	}
	return (builtout_process(matrix, info, mat));
}

void	child_cleanup_and_close(t_info *info)
{
	close(info->fd_in_out[0]);
	close(info->fd_in_out[1]);
	if (info->cpipe[0] > 0 && info->cpipe[0] != STDIN_FILENO
		&& info->cpipe[0] != STDOUT_FILENO)
		close(info->cpipe[0]);
	if (info->cpipe[1] > 0 && info->cpipe[1] != STDIN_FILENO
		&& info->cpipe[1] != STDOUT_FILENO)
		close(info->cpipe[1]);
	if (info->prevpipe > 0 && info->prevpipe != STDIN_FILENO)
		close(info->prevpipe);
	if (info->heredocfd > 0 && info->heredocfd != STDIN_FILENO)
		close(info->heredocfd);
}

int	count_exec_blocks(char ***exec)
{
	int	i;
	int	count;
	int	cmd_rd;

	i = 0;
	count = 0;
	cmd_rd = 0;
	while (exec[i])
	{
		if (!exec[i][0])
		{
			i++;
			continue ;
		}
		process_count_blocks(exec, &i, &count, &cmd_rd);
	}
	if (cmd_rd)
		count++;
	return (count);
}

int	is_heredoc(char **matrix)
{
	if (!matrix || !matrix[0])
		return (0);
	return (ft_strcmp(matrix[0], "<<") == 0);
}

int	*allocate_and_fill_heredocs(void)
{
	int	*array;
	int	i;

	array = malloc(sizeof(int) * 64);
	if (!array)
		return (NULL);
	i = 0;
	while (i < 64)
	{
		array[i] = -42;
		i++;
	}
	return (array);
}
