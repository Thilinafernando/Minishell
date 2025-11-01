/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:11:02 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/29 18:15:26 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_join(t_info *info, char **args, char ***new)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (info->tmp[j])
	{
		(*new)[i] = ft_strdup(info->tmp[j]);
		i++;
		j++;
	}
	j = 0;
	while (args[j])
	{
		if (append((*new), args[j]) != 1)
		{
			(*new)[i] = ft_strdup(args[j]);
			i++;
		}
		j++;
	}
}

char	**matrix_join(t_info *info, char **args, int size)
{
	int		x;
	char	**new;

	x = 0;
	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (x <= size)
	{
		new[x] = NULL;
		x++;
	}
	process_join(info, args, &new);
	free_mat(info->tmp);
	new[size] = NULL;
	return (new);
}

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	sorting(t_info *info)
{
	int	i;
	int	flag;

	matrix_tmp(info);
	flag = 1;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (info->tmp[i + 1])
		{
			if (ft_strcmp(info->tmp[i], info->tmp[i + 1]) > 0)
			{
				swap(&info->tmp[i], &info->tmp[i + 1]);
				flag = 1;
			}
			i++;
		}
	}
}
