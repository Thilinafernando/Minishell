/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:36:36 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/30 15:37:36 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mat(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
		i++;
	i--;
	while (i >= 0 && matrix[i])
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
	matrix = NULL;
	return ;
}

int	if_in(char ***exec, int mat)
{
	mat++;
	while (exec[mat] && exec[mat][0][0] != '|')
	{
		if (ft_strcmp(exec[mat][0], "<") == 0
		|| ft_strcmp(exec[mat][0], "<<") == 0)
			return (1);
		mat++;
	}
	return (0);
}

int	if_out(char ***exec, int mat)
{
	mat++;
	while (exec[mat] && exec[mat][0][0] != '|')
	{
		if (ft_strcmp(exec[mat][0], ">") == 0
		|| ft_strcmp(exec[mat][0], ">>") == 0)
			return (1);
		mat++;
	}
	return (0);
}

void	ft_remove(char ***matrix)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
		{
			if (ft_strcmp(matrix[i][j], ";<") == 0 ||
				ft_strcmp(matrix[i][j], ";>") == 0 ||
				ft_strcmp(matrix[i][j], ";<<") == 0 ||
				ft_strcmp(matrix[i][j], ";>>") == 0)
			{
				tmp = ft_strdup(matrix[i][j] + 1);
				free(matrix[i][j]);
				matrix[i][j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	err_cd(char *arg)
{
	write(2, "Minishell: cd: ", 15);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}
