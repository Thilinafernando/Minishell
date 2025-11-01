/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:39:42 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:51 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	readline_child(char **filename, t_info *info, int *fd, char **str)
{
	if (*str)
		free(*str);
	if (*filename)
		free(*filename);
	if (*fd >= 0)
		close(*fd);
	close_fd(info->cpipe);
	padre(info);
	if (g_signal_status == 130)
		exit(130);
	exit(0);
}

void	ft_heredoc_process(char **exec, t_info *info, char *filename)
{
	int		fd;
	char	*str;

	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (err_fd_heredoc(&filename), free(filename), exit(126));
	while (1)
	{
		str = readline("> ");
		if (!str || !exec[1] || ft_strcmp(str, exec[1]) == 0)
		{
			err_heredoc_null(exec, str);
			readline_child(&filename, info, &fd, &str);
		}
		info->dollar = expand_dollar1(str, info);
		if (info->dollar)
			write_dollar(&info->dollar, fd);
		else
			heredoc_printing_fd(fd, str);
		free(str);
	}
}

int	ft_heredoc_parent(int pid, int *status, t_info *info)
{
	int	fd;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	fd = open (info->heredoc, O_RDONLY);
	if (fd == -1)
		return (err_heredoc_pfd(info), estat(126, info), -1);
	unlink(info->heredoc);
	free(info->heredoc);
	info->heredoc = NULL;
	if (info->heredocfd > 0)
		close(info->heredocfd);
	info->heredocfd = fd;
	set_signals();
	if (parent_signal_handler(status, info) == -1)
		return (-1);
	return (estat(0, info), 0);
}

int	ft_heredoc(char **exec, t_info *info)
{
	int		status;
	pid_t	pid;
	char	*filename;

	filename = heredoc_filename();
	if (!filename)
		return (write(2, "Minishell: failed heredoc filename\n", 35), -1);
	info->heredoc = filename;
	pid = fork();
	if (pid == -1)
		return (free(filename), -1);
	if (pid == 0)
	{
		signal(SIGINT, ctrl_c_here);
		signal(SIGQUIT, SIG_IGN);
		ft_heredoc_process(exec, info, filename);
	}
	else
	{
		if (ft_heredoc_parent(pid, &status, info) == -1)
			return (-1);
	}
	return (0);
}
