/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:32:25 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/28 23:00:04 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*join_word_segment(char *segment, t_token *head,
				t_token **current_word_token, t_token_type type)
{
	if (!segment)
		return (free_tokens(head));
	if (*current_word_token == NULL)
		return (add_new_token_to_list(segment, head, current_word_token, type));
	return (append_to_existing_token(segment, head, current_word_token));
}

t_token	*add_new_token_to_list(char *segment, t_token *head,
				t_token **current_word_token, t_token_type type)
{
	t_token	*new_token;

	new_token = creat_token(segment, type);
	free(segment);
	if (!new_token)
		return (free_tokens(head));
	if (!head)
		head = new_token;
	else
		get_last_token(head)->next = new_token;
	*current_word_token = new_token;
	return (head);
}

t_token	*append_to_existing_token(
	char *segment, t_token *head, t_token **current_word_token)
{
	char	*new_content;

	new_content = ft_strjoin((*current_word_token)->content, segment);
	free(segment);
	if (!new_content)
		return (free_tokens(head));
	free((*current_word_token)->content);
	(*current_word_token)->content = new_content;
	return (head);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	if (s1)
		joined = ft_strjoin(s1, s2);
	else
		joined = ft_strdup(s2);
	free(s1);
	free(s2);
	return (joined);
}

t_token	*process_redirection(t_parse_ctx *ctx)
{
	t_token	*last;

	last = get_last_token(ctx->head);
	ctx->head = handle_redirection(ctx->input, ctx->i, ctx->head, last);
	*(ctx->current_word_token) = NULL;
	return (ctx->head);
}
