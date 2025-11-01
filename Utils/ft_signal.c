/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:15:16 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:51 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	estat(int i, t_info *info)
{
	info->exit_status = i;
}

void	sstat(int i)
{
	g_signal_status = i;
}

void	ctrl_c_here(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	sstat(130);
	rl_replace_line("", 0);
	close(0);
}

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	sstat(131);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
