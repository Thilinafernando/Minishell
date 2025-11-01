/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intergration2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:31:19 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/29 18:44:34 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_redirections(t_info *info, t_token *token)
{
	t_token	*tmp;
	char	**matrix;

	tmp = token;
	while (tmp && tmp->type != 1)
	{
		if (tmp->type == 2 || tmp->type == 3
			|| tmp->type == 4 || tmp->type == 7)
		{
			matrix = malloc(3 * sizeof(char *));
			if (!matrix)
				return ;
			matrix[2] = NULL;
			matrix[0] = ft_strdup(tmp->content);
			matrix[1] = ft_strdup(tmp->next->content);
			info->exec[info->pos] = matrix;
			info->pos++;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

int	size_command(t_token **token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = (*token);
	while (tmp && tmp->type != 1)
	{
		if (tmp->type != 2 && tmp->type != 4
			&& tmp->type != 3 && tmp->type != 7)
			i++;
		if (tmp->type == 2 || tmp->type == 4
			|| tmp->type == 3 || tmp->type == 7)
			tmp = tmp->next->next;
		else
			tmp = tmp->next;
	}
	return (i);
}

void	copy_command(t_token **token, char ***matrix)
{
	int	j;

	j = 0;
	while ((*token) && (*token)->type != 1)
	{
		if ((*token)->type != 2 && (*token)->type != 4
			&& (*token)->type != 3 && (*token)->type != 7)
		{
			if (((*token)->type == 5 || (*token)->type == 6)
				&& ((ft_strcmp((*token)->content, "<") == 0
						|| ft_strcmp((*token)->content, ">") == 0
						|| ft_strcmp((*token)->content, ">>") == 0
						|| ft_strcmp((*token)->content, "<<") == 0)))
				(*matrix)[j] = ft_strjoin(";", (*token)->content);
			else
				(*matrix)[j] = ft_strdup((*token)->content);
			j++;
			(*token) = (*token)->next;
		}
		else
			(*token) = (*token)->next->next;
	}
	(*matrix)[j] = NULL;
}
