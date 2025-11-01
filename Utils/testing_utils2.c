/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:37:02 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/30 15:39:56 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_null(char ***tmp, int count)
{
	int		x;

	x = 0;
	while (x <= count)
	{
		(*tmp)[x] = NULL;
		x++;
	}
}

int	is_val(const char *path, char *str)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (-1);
	if (access(path, X_OK) != 0)
	{
		write(2, "Minishell: ", 11);
		write(2, str, ft_strlen(str));
		write(2, ": permission denied\n", 20);
		return (-1);
	}
	if (!S_ISREG(st.st_mode))
	{
		write(2, "Minishell: ", 11);
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 20);
		return (-1);
	}
	return (1);
}

char	*save_paath(char **envp)
{
	int		i;
	char	*str;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			str = ft_strdup(envp[i] + 5);
			return (str);
		}
		i++;
	}
	return (NULL);
}
