/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkurukul <thilinaetoro4575@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:47:13 by tkurukul          #+#    #+#             */
/*   Updated: 2025/05/29 00:33:48 by tkurukul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd(t_info *info)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		write(2, "pwd: error while retrieving current directory: getcwd\n", 54);
		return (estat(1, info), NULL);
	}
	return (estat(0, info), buf);
}

void	print_pwd(t_info *info)
{
	char	*pwd;

	pwd = ft_pwd(info);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
}
