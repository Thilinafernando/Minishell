/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:40:44 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:51 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc_filename(void)
{
	static int	counter;
	char		*number;
	char		*filename;
	char		*tmp;

	counter = 0;
	number = ft_itoa(counter++);
	if (!number)
		return (NULL);
	tmp = ft_strjoin("/tmp/.heredoc_", number);
	free(number);
	if (!tmp)
		return (NULL);
	filename = ft_strjoin(tmp, ".tmp");
	free(tmp);
	return (filename);
}

/* int	setting_stdin(int *std_in)
{
	(*std_in) = open("/dev/tty", O_RDONLY);
	if ((*std_in) == -1)
	{
		write(2, "Minishell: cannot open /dev/tty\n", 32);
		return (-1);
	}
	if (dup2((*std_in), STDIN_FILENO) == -1)
	{
		write(2, "Minishell: dup2 failed\n", 23);
		close((*std_in));
		return (-1);
	}
	close((*std_in));
	return (0);
} */

void	err_fd_heredoc(char **filename)
{
	write(2, "Minishell : ", 12);
	write(2, (*filename), ft_strlen((*filename)));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

void	err_heredoc_null(char **exec, char *str)
{
	if (!str && g_signal_status != 130)
	{
		write(2, "Minishell: warning: here-document ", 34);
		write(2, "delimited by end-of-file (wanted ", 33);
		write(2, exec[1], ft_strlen(exec[1]));
		write(2, ")\n", 2);
	}
}

void	err_heredoc_pfd(t_info *info)
{
	write(2, "Minishell: ", 11);
	write(2, info->heredoc, ft_strlen(info->heredoc));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}
