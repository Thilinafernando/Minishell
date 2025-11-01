/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pt2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:59:05 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:41:48 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_count_blocks(char ***exec, int *i, int *count, int *cmd_rd)
{
	if (exec[(*i)][0][0] == '|')
	{
		if ((*cmd_rd))
			(*count)++;
		(*cmd_rd) = 0;
	}
	else if (ft_isalpha(exec[(*i)][0][0])
		|| ft_isascii(exec[(*i)][0][0]) || is_redirection(exec[(*i)]))
		(*cmd_rd) = 1;
	(*i)++;
}

int	heredocs(t_info *info)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (info->exec[i])
	{
		if (is_heredoc(info->exec[i]))
		{
			if (info->heredocfd > 0)
				close(info->heredocfd);
			if (ft_heredoc(info->exec[i], info) == -1)
				return (i);
			if (info->heredocfd > 0)
				info->heredocs[flag] = (info->heredocfd);
		}
		else if (info->exec[i][0][0] == '|')
			flag++;
		i++;
	}
	return (0);
}

void	init_exectution(t_info *info)
{
	int	i;

	i = 0;
	info->icount = 0;
	info->cpipe[0] = -1;
	info->cpipe[1] = -1;
	info->fd_in_out[0] = dup(STDIN_FILENO);
	info->fd_in_out[1] = dup(STDOUT_FILENO);
	info->count = count_exec_blocks(info->exec);
	info->pid_counts = 0;
	info->prevpipe = -42;
	info->mat = 0;
	info->heredocfd = -22;
	info->flagheredoc = 0;
	info->flag = 0;
	info->heredocs = allocate_and_fill_heredocs();
	i = heredocs(info);
	if (i != 0)
		info->flagheredoc = i;
}

void	fork_block(t_info *info, pid_t *pid, int *i)
{
	(*pid) = fork();
	if ((*pid) == -1)
	{
		padre(info);
		write(2, "Minishell: error fork\n", 22);
		exit(1);
	}
	if ((*pid) == 0)
		child_block(info, i);
	else
		parent_block(info, i, (*pid));
}

void	final_block(t_info *info)
{
	wait_block(info);
	ft_refresh_fd(info);
	free3(info->exec);
	if (info->cpipe[0] > 0)
		close(info->cpipe[0]);
	if (info->cpipe[1] > 0)
		close(info->cpipe[1]);
	if (info->prevpipe > 0)
		close(info->prevpipe);
	close_fd(info->fd_in_out);
	if (info->heredocfd > 0)
		close (info->heredocfd);
	free_heredocs(&info->heredocs);
}
