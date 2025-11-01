/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:29:40 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 15:34:54 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execution_half(t_info *info, int *i)
{
	if (is_only_redirection(info->exec, info) == 0)
	{
		block_only_rd(info);
		return (-3);
	}
	if (info->count == 1)
	{
		info->flag = is_builtout(info->exec, info);
		if (info->flag == -2)
		{
			ft_refresh_fd(info);
			return (-1);
		}
		if (info->flag == 0)
			return (-1);
	}
	if ((*i) != (info->count - 1))
	{
		if (pipe(info->cpipe) == -1)
		{
			write(2, "Minishell: error pipe\n", 22);
			return (estat(1, info), -2);
		}
	}
	return (0);
}

void	ft_execution(t_info *info)
{
	int		f;
	pid_t	pid;

	init_exectution(info);
	while (info->icount < info->count)
	{
		f = execution_half(info, &info->count);
		if (f == -1)
			break ;
		if (f == -2)
			return ;
		if (f != -3)
			block_rd(info);
		ft_remove(info->exec);
		fork_block(info, &pid, &info->icount);
		info->icount++;
	}
	final_block(info);
}
