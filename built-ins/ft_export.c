/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 01:47:10 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/30 15:36:27 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printing_process(t_info *info, int *i)
{
	int	j;
	int	flag;

	flag = 0;
	j = -1;
	while (info->tmp[(*i)][++j])
	{
		write(1, &info->tmp[(*i)][j], 1);
		if (info->tmp[(*i)][j] == '=' && flag == 0)
		{
			write(1, "\"", 1);
			flag = 1;
		}
		if (!info->tmp[(*i)][j + 1] && flag != 0)
			write(1, "\"", 1);
	}
}

void	print_export(t_info *info)
{
	int	i;

	i = -1;
	sorting(info);
	while (info->tmp[++i])
	{
		if (ft_strncmp(info->tmp[i], "_=", 2) == 0)
			continue ;
		write(1, "declare -x ", 11);
		printing_process(info, &i);
		write(1, "\n", 1);
	}
	free_mat(info->tmp);
}

void	verify_loop(char **args, t_info *info, int *count)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if ((verify(args[i]) != 0))
		{
			write(2, "Minishell: export: '", 20);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "' : not a valid identifier\n", 27);
			estat(1, info);
		}
		else
			(*count)++;
		i++;
	}
}

void	copy_loop(char **args, char ***tmp)
{
	int	j;
	int	i;

	i = 1;
	j = 0;
	while (args[i])
	{
		if ((verify(args[i]) == 0))
		{
			(*tmp)[j] = ft_strdup(args[i]);
			j++;
		}
		i++;
	}
	(*tmp)[j] = NULL;
}

void	ft_export(t_info *info, char **args)
{
	int		count;
	char	**tmp;

	count = 0;
	if (!args[1])
	{
		print_export(info);
		return (estat(0, info));
	}
	verify_loop(args, info, &count);
	tmp = malloc((count + 1) * sizeof(char *));
	if (!tmp)
		return ;
	fill_null(&tmp, count);
	copy_loop(args, &tmp);
	matrix_tmp(info);
	free_mat(info->env);
	info->size += count;
	info->env = matrix_join(info, tmp, info->size);
	free_mat(tmp);
	return (estat(info->exit_status, info));
}
