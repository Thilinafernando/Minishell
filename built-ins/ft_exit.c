/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:23:50 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/30 21:41:08 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i] && (str[0] == '-' || str[0] == '+'))
		return (-1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (0);
}

int	exit_arg_checks(char **args, t_info *info)
{
	if (args[1])
	{
		if (is_num(args[1]) == -1)
		{
			write(2, "Minishell: exit: ", 17);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 28);
			padre(info);
			exit(2);
		}
	}
	if (args[2])
	{
		write(2, "Minishell: exit: too many arguments\n", 36);
		return (estat(1, info), -1);
	}
	return (0);
}

void	ft_exit(char **args, t_info *info)
{
	int		num;

	write(1, "exit\n", 5);
	if (args[1])
	{
		if (exit_arg_checks(args, info) == -1)
			return ;
		num = ft_atoi(args[1]);
		if (num < 0)
			info->exit_status = 256 + num;
		else
			info->exit_status = num;
	}
	free_all(info);
	exit(info->exit_status);
}

void	ft_pipe_exit(char **args, t_info *info)
{
	int		num;

	if (args[1])
	{
		if (exit_arg_checks(args, info) == -1)
			return ;
		num = ft_atoi(args[1]);
		if (num < 0)
			info->exit_status = 256 + num;
		else
			info->exit_status = num;
	}
	free_all(info);
	exit(info->exit_status);
}
