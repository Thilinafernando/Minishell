/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:25:55 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/06/03 17:31:51 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_single_quote_content(char *input, int *i)
{
	int		content_start;
	char	quote_char;
	char	*content;

	content_start = *i + 1;
	quote_char = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (!input[*i])
	{
		printf("error: unif_closed quote\n");
		return (NULL);
	}
	content = ft_substr(input, content_start, *i - content_start);
	(*i)++;
	return (content);
}

char	*extract_double_quote_content(char *input, int *i, t_info *info)
{
	int		content_start;
	char	*full_segment;

	(*i)++;
	content_start = *i;
	full_segment = NULL;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$' && (ft_isalnum(input[*i + 1])
				|| input[*i + 1] == '_' || input[*i + 1] == '?'))
		{
			if (!append_text_segment(input, i, content_start, &full_segment))
				return (NULL);
			if (!process_variable(input, i, info, &full_segment))
				return (NULL);
			content_start = *i;
		}
		else
			(*i)++;
	}
	return (handle_quote_end(input, i, content_start, full_segment));
}

t_token	*process_single_quote(t_parse_ctx *ctx)
{
	char	*segment;

	segment = extract_single_quote_content(ctx->input, ctx->i);
	if (!segment)
		return (free_tokens(ctx->head));
	ctx->head = join_word_segment(segment, ctx->head,
			ctx->current_word_token, TOKEN_SQUOTE);
	return (ctx->head);
}

t_token	*process_double_quote(t_parse_ctx *ctx)
{
	char	*segment;

	segment = extract_double_quote_content(ctx->input, ctx->i, ctx->info);
	if (!segment)
		return (free_tokens(ctx->head));
	ctx->head = join_word_segment(segment, ctx->head,
			ctx->current_word_token, TOKEN_DQUOTE);
	return (ctx->head);
}

char	*handle_quote_end(char *input, int *i, int content_start,
						char *full_segment)
{
	if (!append_text_segment(input, i, content_start, &full_segment))
		return (NULL);
	if (!input[*i])
	{
		write(2, "Minishell: syntax error: unclosed double quote\n", 47);
		free(full_segment);
		return (NULL);
	}
	(*i)++;
	if (!full_segment)
		return (ft_strdup(""));
	return (full_segment);
}
