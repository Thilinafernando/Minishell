/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:00:59 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/31 21:37:03 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirections(char **matrix, t_info *info)
{
	int	result;

	result = 0;
	if (ft_strcmp(matrix[0], "<") == 0)
		result = ft_input(matrix, info);
	else if (ft_strcmp(matrix[0], ">") == 0)
		result = ft_output(matrix, info);
	else if (ft_strcmp(matrix[0], ">>") == 0)
		result = ft_append(matrix, info);
	else if (ft_strcmp(matrix[0], "<<") == 0)
	{
		if (info->flagheredoc != 0 && info->icount == info->flagheredoc)
			return (-1);
		if (info->heredocs[info->icount] > 0)
			info->fd_in_child = info->heredocs[info->icount];
	}
	if (result == -1)
		return (-1);
	return (0);
}

int	is_redirection(char **matrix)
{
	if (!matrix || !matrix[0])
		return (0);
	return (ft_strcmp(matrix[0], "<") == 0
		|| ft_strcmp(matrix[0], ">") == 0
		|| ft_strcmp(matrix[0], ">>") == 0
		|| ft_strcmp(matrix[0], "<<") == 0);
}

int	is_builtin(char **matrix)
{
	if (!matrix || !matrix[0])
		return (0);
	if (ft_strcmp(matrix[0], "cd") == 0
		|| ft_strcmp(matrix[0], "pwd") == 0
		|| ft_strcmp(matrix[0], "unset") == 0
		|| ft_strcmp(matrix[0], "export") == 0
		|| ft_strcmp(matrix[0], "env") == 0
		|| ft_strcmp(matrix[0], "echo") == 0
		|| ft_strcmp(matrix[0], "exit") == 0)
		return (1);
	return (0);
}

void	exec_builtin(char **matrix, t_info *info)
{
	if (ft_strcmp(matrix[0], "cd") == 0)
		ft_cd(matrix, info);
	else if (ft_strcmp(matrix[0], "pwd") == 0)
		print_pwd(info);
	else if (ft_strcmp(matrix[0], "unset") == 0)
		ft_unset(info, matrix);
	else if (ft_strcmp(matrix[0], "export") == 0)
		ft_export(info, matrix);
	else if (ft_strcmp(matrix[0], "env") == 0)
		ft_env(matrix, info);
	else if (ft_strcmp(matrix[0], "echo") == 0)
		ft_echo(matrix, info);
	else if (ft_strcmp(matrix[0], "exit") == 0)
		ft_pipe_exit(matrix, info);
}

int	builtout_process(char ***matrix, t_info *info, int mat)
{
	int	i;

	i = 0;
	if (ft_strcmp(matrix[mat][0], "cd") == 0)
		ft_cd(matrix[mat], info);
	else if (ft_strcmp(matrix[mat][0], "pwd") == 0)
		print_pwd(info);
	else if (ft_strcmp(matrix[mat][0], "unset") == 0)
		ft_unset(info, matrix[mat]);
	else if (ft_strcmp(matrix[mat][0], "export") == 0)
		ft_export(info, matrix[mat]);
	else if (ft_strcmp(matrix[mat][0], "env") == 0)
		ft_env(matrix[mat], info);
	else if (ft_strcmp(matrix[mat][0], "echo") == 0)
		ft_echo(matrix[mat], info);
	else if (ft_strcmp(matrix[mat][0], "exit") == 0)
		ft_exit(matrix[mat], info);
	else
		i = -1;
	return (i);
}
