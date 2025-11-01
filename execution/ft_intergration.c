/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intergration.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:19:42 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/29 22:58:45 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_command(t_info *info, t_token **token)
{
	int		i;
	char	**matrix;

	i = size_command(token);
	save_redirections(info, (*token));
	if (i == 0)
	{
		while ((*token) && (*token)->type != 1)
			(*token) = (*token)->next;
		return ;
	}
	matrix = malloc((i + 1) * sizeof(char *));
	if (!matrix)
		return ;
	copy_command(token, &matrix);
	info->exec[info->pos] = matrix;
	info->pos++;
	return ;
}

void	save_other(t_info *info, t_token **token)
{
	char	**matrix;

	matrix = malloc(2 * sizeof(char *));
	if (!matrix)
		return ;
	matrix[0] = ft_strdup((*token)->content);
	matrix[1] = NULL;
	(*token) = (*token)->next;
	info->exec[info->pos] = matrix;
	info->pos++;
}

void	ft_conditions(t_info *info, t_token **token)
{
	if ((*token)->type != 1)
		save_command(info, token);
	else
		save_other(info, token);
}

int	size_main_matrix(t_token *token)
{
	int		size;
	t_token	*tmp;

	size = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == 0 || tmp->type == 5
			|| tmp->type == 6 || tmp->type == 8)
			size++;
		if ((tmp->type == 2 || tmp->type == 3
				|| tmp->type == 4 || tmp->type == 7)
			&& tmp->next != NULL)
		{
			size++;
			tmp = tmp->next->next;
			continue ;
		}
		if (tmp->type == 1)
			size++;
		tmp = tmp->next;
	}
	return (size);
}

void	form_main(t_token *token, t_info *info)
{
	int		i;
	int		size;
	char	***matrix;

	size = size_main_matrix(token);
	matrix = malloc((size + 1) * sizeof(char **));
	if (!matrix)
		return ;
	i = size;
	while (i >= 0)
	{
		matrix[i] = NULL;
		i--;
	}
	info->exec = matrix;
	info->pos = 0;
	while (token)
		ft_conditions(info, &token);
}
