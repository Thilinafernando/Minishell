/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:16:54 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/30 16:35:05 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*tokenize_input(char *input, t_info *info)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	if (!parse_tokens_loop(input, &i, info, &head))
		return (NULL);
	return (head);
}

/* int	parse_tokens_loop(char *input, int *i,
	t_info *info, t_token **head)
{
	t_parse_ctx		ctx;
	t_token			*current_word_token;

	current_word_token = NULL;
	ctx.info = info;
	ctx.current_word_token = &current_word_token;
	while (input[*i])
	{
		if (input[*i] == ' ' || input[*i] == '\t')
		{
			current_word_token = NULL;
			(*i)++;
		}
		else if (ft_strchr("|<>\'\"", input[*i]))
		{
			*head = handle_special_chars(input, i, *head, &ctx);
			if (!*head)
				return (0);
		}
		else if (input[*i] == '$')
		{
			*head = handle_env_variable(input, i, *head, &ctx);
			if (!*head)
				return (0);
		}
		else if (!handle_word_segment(input, i, head, &current_word_token))
			return (0);
	}
	return (1);
} */

static int	process_current_char(char *input, int *i,
	t_token **head, t_parse_ctx *ctx)
{
	if (input[*i] == ' ' || input[*i] == '\t')
	{
		*(ctx->current_word_token) = NULL;
		(*i)++;
	}
	else if (ft_strchr("|<>\'\"", input[*i]))
	{
		*head = handle_special_chars(input, i, *head, ctx);
		if (!*head)
			return (0);
	}
	else if (input[*i] == '$')
	{
		*head = handle_env_variable(input, i, *head, ctx);
		if (!*head)
			return (0);
	}
	else if (!handle_word_segment(input, i, head, ctx->current_word_token))
		return (0);
	return (1);
}

int	parse_tokens_loop(char *input, int *i,
	t_info *info, t_token **head)
{
	t_parse_ctx		ctx;
	t_token			*current_word_token;

	current_word_token = NULL;
	ctx.info = info;
	ctx.current_word_token = &current_word_token;
	while (input[*i])
	{
		if (!process_current_char(input, i, head, &ctx))
			return (0);
	}
	return (1);
}

int	handle_word_segment(char *input, int *i, t_token **head,
							t_token **current_word_token)
{
	char	*segment;

	segment = extract_word_segment(input, i);
	if (!segment)
		return (1);
	*head = join_word_segment(segment, *head, current_word_token, TOKEN_WORD);
	if (!*head)
	{
		free(segment);
		return (0);
	}
	return (1);
}

char	*extract_word_segment(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_strchr(" \t|><\'\"$", input[*i]))
		(*i)++;
	if (*i > start)
		return (ft_substr(input, start, *i - start));
	return (NULL);
}
/*
void	debug_print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("Token %d: [%s] (type: %d)\n",
			i++, tokens->content, tokens->type);
		tokens = tokens->next;
	}
} */
