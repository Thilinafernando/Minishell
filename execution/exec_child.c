/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:54:04 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:33:27 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_exec_cond(char **command, t_info *info, int **fd, char **str)
{
	if (ft_strcmp("GG", (*str)) == 0)
	{
		free((*str));
		close_fd((*fd));
		free_all(info);
		exit(127);
	}
	if (is_directory((*str)) == 1 || is_val((*str), command[0]) == -1)
	{
		free((*str));
		close_fd((*fd));
		free_all(info);
		exit(126);
	}
}

void	one_exec(char **command, t_info *info, int fd[2])
{
	char	*str;

	if (command[0][0] == '\0')
		return (write(2, "Minishell: '': command not found\n", 33),
			close_fd(fd), free_all(info), exit(127));
	if (is_directory(command[0]) == 1)
	{
		close_fd(fd);
		free_all(info);
		exit(126);
	}
	str = NULL;
	str = abs_path(command[0], info);
	if (!str)
	{
		failure_command(fd, command, info);
		free_all(info);
		exit (info->exit_status);
	}
	one_exec_cond(command, info, &fd, &str);
	execve(str, command, info->env);
	failure(fd, info);
	free_all(info);
	free(str);
	exit (126);
}

void	child_pt2(t_info *info)
{
	if (info->fd_in_child > 0)
	{
		if (dup2(info->fd_in_child, 0) == -1)
			return (write(2, "Minishell: error dup2\n", 22)
				, free_all(info), exit(1));
		else
			close(info->fd_in_child);
	}
	if (info->fd_out_child > 0)
	{
		if (dup2(info->fd_out_child, 1) == -1)
			return (write(2, "Minishell: error dup2\n", 22)
				, free_all(info), exit(1));
		else
			close(info->fd_out_child);
	}
}

void	child_pt1(t_info *info, int *i)
{
	signal(SIGPIPE, SIG_IGN);
	if ((*i) != 0 && info->prevpipe > 0)
	{
		if (dup2(info->prevpipe, 0) == -1)
		{
			ft_printf(2, "strerr: %s\n", strerror(errno));
			return (write(2, "Minishell: error dup2\n", 22)
				, free_all(info), exit(1));
		}
		else
		{
			close(info->prevpipe);
			info->prevpipe = -1;
		}
	}
	if ((*i) != (info->count - 1))
	{
		if (info->cpipe[0] > 0)
			close(info->cpipe[0]);
		if (dup2(info->cpipe[1], 1) == -1)
			return (write(2, "Minishell: error dup2\n", 22)
				, free_all(info), exit(1));
		else
			close(info->cpipe[1]);
	}
}

void	child_block(t_info *info, int *i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_pt1(info, i);
	child_pt2(info);
	child_cleanup_and_close(info);
	if (info->flag == 1)
	{
		free_all(info);
		exit(info->exit_status);
	}
	if (is_builtin(info->exec[info->mat]))
	{
		exec_builtin(info->exec[info->mat], info);
		free_all(info);
		exit(info->exit_status);
	}
	else
		one_exec(info->exec[info->mat], info, info->cpipe);
}
