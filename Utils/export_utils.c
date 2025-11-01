/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:09:23 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/30 19:59:10 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verify(char	*str)
{
	int	i;

	i = 0;
	if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
		return (-1);
	else
		i++;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| ((str[i] >= 'A' && str[i] <= 'Z')) || str[i] == '_'
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == 61 || str[i] == '"' || str[i] == 39)
			i++;
		else
			return (-1);
	}
	return (0);
}

int	verify_equal(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 61)
			count = 1;
		i++;
	}
	if (count != 1)
		return (-1);
	return (0);
}

int	exisit(char **matrix, char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], arg, len) == 0
			&& (matrix[i][len] == '=' || matrix[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	matrix_tmp(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->env[i])
		i++;
	info->size = i;
	info->tmp = malloc((i + 1) * sizeof(char *));
	if (!info->tmp)
		return ;
	while (info->env[j])
	{
		info->tmp[j] = ft_strdup(info->env[j]);
		j++;
	}
	info->tmp[j] = NULL;
	return ;
}

int	append(char **matrix, char *args)
{
	int	pos;
	int	flag;

	flag = 0;
	pos = exisit(matrix, args);
	if (pos != -1)
	{
		if ((verify_equal(args) == -1) && (verify_equal(matrix[pos]) == 0))
			flag = 1;
		else
		{
			free(matrix[pos]);
			matrix[pos] = ft_strdup(args);
		}
		flag = 1;
	}
	return (flag);
}
