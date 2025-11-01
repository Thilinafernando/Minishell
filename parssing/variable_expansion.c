/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:29:08 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/30 19:07:44 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*handle_env_variable(char *input, int *i,
	t_token *head, t_parse_ctx *ctx)
{
	char	*var_value;

	if (input[*i + 1] == '?')
	{
		var_value = mdollar("?", ctx->info);
		*i += 2;
	}
	else if (input[*i + 1] && (ft_isalnum(input[*i + 1])
			|| input[*i + 1] == '_'))
	{
		var_value = get_named_var_value(input, i, ctx->info);
		if (!var_value)
			var_value = ft_strdup("");
	}
	else
	{
		var_value = ft_strdup("$");
		(*i)++;
	}
	head = join_word_segment(var_value, head,
			ctx->current_word_token, TOKEN_VAR);
	return (head);
}

char	*get_named_var_value(char *input, int *i, t_info *info)
{
	int		var_start;
	char	*var_name;
	char	*var_value;

	var_start = *i + 1;
	while (input[*i] && (ft_isalnum(input[*i + 1]) || input[*i + 1] == '_'))
		(*i)++;
	var_name = ft_substr(input, var_start, *i - var_start + 1);
	if (!var_name)
		return (NULL);
	var_value = mdollar(var_name, info);
	free(var_name);
	(*i)++;
	return (var_value);
}

char	*process_named_variable(char *input, int *i, t_info *info)
{
	int		var_start;
	char	*var_name;
	char	*var_value;

	var_start = *i + 1;
	while (input[*i] && (ft_isalnum(input[*i + 1]) || input[*i + 1] == '_'))
		(*i)++;
	var_name = ft_substr(input, var_start, *i - var_start + 1);
	if (!var_name)
		return (NULL);
	var_value = mdollar(var_name, info);
	free(var_name);
	(*i)++;
	return (var_value);
}

int	process_variable(char *input, int *i, t_info *info, char **full_segment)
{
	char	*var_value;

	if (input[*i + 1] == '?')
	{
		var_value = mdollar("?", info);
		*i += 2;
	}
	else if (input[*i + 1] && (ft_isalnum(input[*i + 1])
			|| input[*i + 1] == '_'))
		var_value = process_named_variable(input, i, info);
	else
	{
		var_value = ft_strdup("$");
		(*i)++;
	}
	if (var_value)
	{
		*full_segment = join_and_free(*full_segment, var_value);
		if (!*full_segment)
			return (0);
	}
	return (1);
}

int	append_text_segment(char *input, int *i, int content_start,
		char **full_segment)
{
	char	*segment;

	if (*i > content_start)
	{
		segment = ft_substr(input, content_start, *i - content_start);
		if (!segment)
			return (0);
		*full_segment = join_and_free(*full_segment, segment);
		if (!*full_segment)
			return (0);
	}
	return (1);
}
