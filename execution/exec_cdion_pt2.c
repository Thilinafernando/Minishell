/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cdion_pt2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:02:24 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:51 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtout_re(char ***matrix, t_info *info)
{
	int	mat;

	mat = 0;
	while (is_redirection(matrix[mat]))
	{
		if (ft_redirections(matrix[mat], info) == -1)
			return (-2);
		if (if_in(matrix, mat) == 1 && info->fd_in_child > 0)
		{
			close(info->fd_in_child);
			info->fd_in_child = -42;
		}
		if (if_out(matrix, mat) == 1 && info->fd_out_child > 0)
		{
			close(info->fd_out_child);
			info->fd_out_child = -42;
		}
		mat++;
	}
	return (mat);
}

int	is_builtout(char ***matrix, t_info *info)
{
	int	mat;
	int	result;

	mat = 0;
	while (is_redirection(matrix[mat]))
		mat++;
	if (is_builtin(matrix[mat]) != 1)
		return (-1);
	mat = builtout_re(matrix, info);
	if (mat == -2)
		return (-2);
	ft_remove(matrix);
	result = handle_builtin_redirection(matrix, info, mat);
	return (result);
}

int	is_only_redirection(char ***matrix, t_info *info)
{
	int	i;

	i = info->mat;
	while (matrix[i] && matrix[i][0][0] != '|')
	{
		if (!(matrix[i][0]) ||
			!(ft_strcmp(matrix[i][0], "<") == 0 ||
			ft_strcmp(matrix[i][0], ">") == 0 ||
			ft_strcmp(matrix[i][0], "<<") == 0 ||
			ft_strcmp(matrix[i][0], ">>") == 0))
			return (-1);
		i++;
	}
	return (0);
}

void	block_only_rd(t_info *info)
{
	int	i;

	while (info->exec[info->mat])
	{
		i = ft_redirections(info->exec[info->mat], info);
		if (i == -1)
		{
			info->flag = 1;
			return ;
		}
		if (if_in(info->exec, info->mat) == 1 && info->fd_in_child > 0)
		{
			close(info->fd_in_child);
			info->fd_in_child = -42;
		}
		if (if_out(info->exec, info->mat) == 1 && info->fd_out_child > 0)
		{
			close(info->fd_out_child);
			info->fd_out_child = -42;
		}
		info->mat++;
	}
	info->flag = 1;
}

void	block_rd(t_info *info)
{
	info->flag = 0;
	while (is_redirection(info->exec[info->mat])
		&& info->exec[info->mat][0][0] != '|')
	{
		if (ft_redirections(info->exec[info->mat], info) == -1)
		{
			info->flag = 1;
			break ;
		}
		if (if_in(info->exec, info->mat) == 1 && info->fd_in_child > 0)
		{
			close(info->fd_in_child);
			info->fd_in_child = -42;
		}
		if (if_out(info->exec, info->mat) == 1 && info->fd_out_child > 0)
		{
			close(info->fd_out_child);
			info->fd_out_child = -42;
		}
		info->mat++;
	}
}
