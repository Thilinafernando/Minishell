/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:46:45 by tkurukul          #+#    #+#             */
/*   Updated: 2025/06/03 17:41:55 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*home_path(t_info *info)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (info->env[i])
	{
		if (ft_strncmp(info->env[i], "HOME=", 5) == 0)
			str = ft_strdup(info->env[i] + 5);
		i++;
	}
	if (!str)
		return (NULL);
	return (str);
}

int	matlen(char	**matrix)
{
	int		i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}

int	update_oldpwd(char ***matrix, t_info *info)
{
	int		i;
	char	*oldpwd;
	char	*pwd;

	i = -1;
	pwd = ft_pwd(info);
	if (!pwd)
		return (-1);
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (oldpwd == NULL)
		return (-1);
	free(pwd);
	while ((*matrix)[++i])
	{
		if (ft_strncmp((*matrix)[i], "OLDPWD=", 7) == 0)
		{
			free((*matrix)[i]);
			(*matrix)[i] = oldpwd;
			return (0);
		}
	}
	free(oldpwd);
	return (0);
}

int	update_pwd(char ***matrix, t_info *info)
{
	int		i;
	char	*newpwd;
	char	*join;

	i = 0;
	newpwd = ft_pwd(info);
	join = ft_strjoin("PWD=", newpwd);
	free (newpwd);
	if (join == NULL)
		return (-1);
	while ((*matrix)[i])
	{
		if (ft_strncmp((*matrix)[i], "PWD=", 4) == 0)
		{
			free((*matrix)[i]);
			(*matrix)[i] = join;
			return (0);
		}
		i++;
	}
	free (join);
	return (-1);
}

void	ft_cd(char **args, t_info *info)
{
	char	*home;

	home = NULL;
	home = home_path(info);
	if (args[1] && args[2])
		return (write(2, "Minishell: cd: too many arguments\n", 34),
			free(home), estat(1, info));
	if (args[1] == NULL || args[1][0] == '\0'
			|| (ft_strcmp(args[1], "~") == 0))
		return (cd_home(info, &home));
	else if (args[1])
	{
		update_oldpwd(&info->env, info);
		if (chdir(args[1]) != 0)
			return (err_cd(args[1]), free(home), estat(1, info));
		update_pwd(&info->env, info);
		return (free(home), estat(0, info));
	}
	if (home)
		free(home);
	return (estat(1, info));
}
