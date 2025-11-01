/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:59:37 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/05/30 20:34:24 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_syntax(t_token *tokens, t_info *info, t_token *prev)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			if (!prev || !tokens->next || tokens->next->type == TOKEN_PIPE)
			{
				ft_printf(2, "Minishell: syntax error: unexpected token `%s'\n",
					token_type_to_string(TOKEN_PIPE));
				return (estat(2, info), 0);
			}
		}
		else if (tokens->type == 2 || tokens->type == 3
			|| tokens->type == 4 || tokens->type == 7)
		{
			if (!tokens->next || tokens->next->type != TOKEN_WORD)
			{
				ft_printf(2, "Minishell: syntax error: unexpected token `%s'\n",
					token_type_to_string(tokens->type));
				return (estat(2, info), 0);
			}
		}
		prev = tokens;
		tokens = tokens->next;
	}
	return (1);
}

char	*token_type_to_string(t_token_type token_type)
{
	if (token_type == TOKEN_WORD)
		return ("word");
	else if (token_type == TOKEN_PIPE)
		return ("|");
	else if (token_type == TOKEN_REDIR_IN)
		return ("<");
	else if (token_type == TOKEN_REDIR_OUT)
		return (">");
	else if (token_type == TOKEN_REDIR_APPEND)
		return (">>");
	else if (token_type == TOKEN_SQUOTE)
		return ("'");
	else if (token_type == TOKEN_DQUOTE)
		return ("\"");
	else if (token_type == TOKEN_HEREDOC)
		return ("<<");
	else if (token_type == TOKEN_VAR)
		return ("$");
	else if (token_type == TOKEN_SPACE)
		return (" ");
	else
		return ("unknown");
}
