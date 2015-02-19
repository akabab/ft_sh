/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 19:12:50 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 14:41:34 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int		get_env_len(char **g_env)
{
	int		len;

	len = 0;
	while (g_env && *g_env)
	{
		len++;
		g_env++;
	}
	return (len);
}

int		get_env_value_index(char *name)
{
	int		index;
	char	*tmp;

	index = 0;
	tmp = ft_strjoin(name, "=");
	while (g_env && g_env[index])
	{
		if ((ft_strstr(g_env[index], tmp)) != NULL)
			return (index);
		index++;
	}
	return (-1);
}

char	*get_env_value(char *name)
{
	char	*value;
	int		index;

	index = get_env_value_index(name);
	if (index == -1)
		return (NULL);
	value = g_env[index] + ft_strlen(name) + 1;
	return (value);
}

int		del_env_value(char *name)
{
	int		env_len;
	int		index;

	env_len = get_env_len(g_env);
	index = get_env_value_index(name);
	if (index != -1)
	{
		while (index < env_len)
		{
			g_env[index] = g_env[index + 1];
			index++;
		}
		return (1);
	}
	return (0);
}

int		add_env_value(char *name, char *value)
{
	int		env_len;
	int		index;
	char	*tmp;

	env_len = get_env_len(g_env);
	if ((index = get_env_value_index(name)) != -1)
	{
		tmp = g_env[index];
		g_env[index] = ft_strjoin3(name, "=", value);
		free(tmp);
	}
	else if (env_len < ENV_SIZE)
		g_env[env_len] = ft_strjoin3(name, "=", value);
	else
		return (0);
	return (1);
}
