/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:10:33 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/30 17:05:17 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal_status = 0;

int	main(int ac, char **av, char **env)
{
	t_token	*token;
	t_info	info;
	char	*line;

	token = NULL;
	if (first_setting(&info, ac, av, env) == -1)
		return (1);
	using_history();
	while (1)
	{
		init_loop(&info);
		line = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (g_signal_status == 131)
			signal_reciever(&info);
		if (line_condition(&line, token, &info) == 1)
			continue ;
		free(line);
	}
	return (clear_history(), last_setting(&info), 0);
}
