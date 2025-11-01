/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 22:13:33 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/30 15:36:14 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "-n", 2) == 0)
		i = 2;
	else
		return (-1);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (-1);
	}
	return (0);
}

int	checks(char **args, int i, int flag)
{
	if ((ft_strncmp(args[i], "-n", 2) != 0) && args[i][0] == '\0')
		return (flag);
	if ((ft_strncmp(args[i], "-n", 2) != 0)
		|| (ft_strncmp(args[i], "-n", 2) == 0
			&& is_n(args[i]) != 0))
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		flag = 0;
	}
	else if ((ft_strncmp(args[i], "-n", 2) == 0) && flag != 1)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
	}
	return (flag);
}

int	ft_echo(char **args, t_info *info)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!args[1])
		return (write(1, "\n", 1), 0);
	while (args[i])
	{
		if ((ft_strncmp(args[1], "-n", 2) == 0 && i == 1 && is_n(args[i]) == 0))
			flag = 1;
		else
			checks(args, i, flag);
		i++;
	}
	if (flag != 1)
		write(1, "\n", 1);
	return (estat(0, info), 0);
}
