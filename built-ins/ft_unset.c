/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:48:21 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/29 22:43:28 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	proccess(t_info *info, char **args)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	while (info->tmp[i])
		i++;
	size = i - (calcu(args, info) - dups(args));
	info->env = malloc((size + 1) * sizeof(char *));
	if (!info->env)
		return (estat(1, info));
	i = 0;
	j = 0;
	while (info->tmp[i])
	{
		if (yes_unset(info, args, i) == 0)
		{
			info->env[j] = ft_strdup(info->tmp[i]);
			j++;
		}
		i++;
	}
	info->env[size] = NULL;
	free_mat(info->tmp);
}

void	ft_unset(t_info *info, char **args)
{
	if (!args[1] || args[1][0] == '\0')
		return (estat(0, info));
	matrix_tmp(info);
	free_mat(info->env);
	proccess(info, args);
	return (estat(info->exit_status, info));
}
