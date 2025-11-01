/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:22:11 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/28 22:59:59 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*handle_special_chars(char *input, int *i,
	t_token *head, t_parse_ctx *full_ctx)
{
	t_parse_ctx	ctx;

	ctx = *full_ctx;
	ctx.input = input;
	ctx.i = i;
	ctx.head = head;
	if (input[*i] == '|')
		return (process_pipe(&ctx));
	else if (input[*i] == '<' || input[*i] == '>')
		return (process_redirection(&ctx));
	else if (input[*i] == '\'')
		return (process_single_quote(&ctx));
	else if (input[*i] == '"')
		return (process_double_quote(&ctx));
	return (head);
}

t_token	*handle_pipe(int *i, t_token *head, t_token *current)
{
	t_token	*new_token;

	new_token = creat_token("|", TOKEN_PIPE);
	if (!new_token)
		return (free_tokens(head));
	if (!head)
		head = new_token;
	else
		current->next = new_token;
	(*i)++;
	return (head);
}

t_token	*handle_redirection(char *input, int *i,
				t_token *head, t_token *current)
{
	t_token	*new_token;

	new_token = NULL;
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			new_token = creat_token("<<", TOKEN_HEREDOC);
			*i += 2;
		}
		else
		{
			new_token = creat_token("<", TOKEN_REDIR_IN);
			(*i)++;
		}
	}
	else if (input[*i] == '>')
		new_token = handle_redirection_append(input, i);
	if (!new_token)
		return (free_tokens(head));
	if (!head)
		head = new_token;
	else
		current->next = new_token;
	return (head);
}

t_token	*handle_redirection_append(char *input, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			new_token = creat_token(">>", TOKEN_REDIR_APPEND);
			*i += 2;
		}
		else
		{
			new_token = creat_token(">", TOKEN_REDIR_OUT);
			(*i)++;
		}
	}
	return (new_token);
}

t_token	*process_pipe(t_parse_ctx *ctx)
{
	t_token	*last;

	last = get_last_token(ctx->head);
	ctx->head = handle_pipe(ctx->i, ctx->head, last);
	*(ctx->current_word_token) = NULL;
	return (ctx->head);
}
