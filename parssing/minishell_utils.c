/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:11:07 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:51 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_setting(t_info *info, int ac, char **av, char **env)
{
	if (ac != 1 || av[1])
	{
		write(2, "Error: Invalid arguments\n", 25);
		return (-1);
	}
	form_env(env, info);
	info->exit_status = 0;
	return (0);
}

void	last_setting(t_info *info)
{
	free_mat(info->env);
	close (1);
	close (2);
	close (0);
}

int	line_condition(char **line, t_token *token, t_info *info)
{
	if ((*line)[0] != '\0')
	{
		add_history((*line));
		token = tokenize_input((*line), info);
		if (!token)
		{
			free((*line));
			return (1);
		}
		if (!validate_syntax(token, info, NULL))
		{
			free_tokens(token);
			return (1);
		}
		if (token)
			act_block(token, info);
	}
	return (0);
}

void	act_block(t_token *token, t_info *info)
{
	form_main(token, info);
	free_tokens(token);
	ft_execution(info);
}

void	init_loop(t_info *info)
{
	set_signals();
	info->exec = NULL;
	info->pos = 0;
	info->tmp = NULL;
	info->size = 0;
	info->fd_in_child = -42;
	info->fd_out_child = -42;
	info->dollar = NULL;
	info->heredoc = NULL;
	info->pid_counts = 0;
	info->dollar = NULL;
	info->line = NULL;
}
