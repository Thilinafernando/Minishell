/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:12:21 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/29 19:45:47 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_unset(char *str)
{
	write(2, "Minishell: unset: ", 18);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 25);
}

int	verify_unset(char *str, t_info *info)
{
	int	i;

	i = 0;
	if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
	{
		err_unset(str);
		return (estat(0, info), -1);
	}
	else
		i++;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| ((str[i] >= 'A' && str[i] <= 'Z'))
			|| str[i] == '_' || (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
		{
			err_unset(str);
			estat(0, info);
			return (-1);
		}
	}
	return (0);
}

int	calcu(char **args, t_info *info)
{
	int	i;
	int	size;

	i = 1;
	size = 0;
	while (args[i])
	{
		if (((verify_unset(args[i], info) == 0)
				&& exisit(info->tmp, args[i]) != -1))
			size++;
		i++;
	}
	return (size);
}

int	dups(char **args)
{
	int	i;
	int	j;
	int	count;

	i = 1;
	count = 0;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (ft_strcmp(args[i], args[j]) == 0)
			{
				count++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	yes_unset(t_info *info, char **args, int i)
{
	int	x;
	int	len;

	x = 1;
	while (args[x])
	{
		len = ft_strlen(args[x]);
		if (ft_strncmp(args[x], info->tmp[i], len) == 0
			&& (info->tmp[i][len] == '='
			|| info->tmp[i][len] == '\0') && (verify_unset(args[x], info) == 0))
			return (1);
		x++;
	}
	return (0);
}
