/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 19:12:50 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/19 14:16:01 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int		get_env_len(void)
{
	int		len;

	len = 0;
	while (g_env && g_env[len])
		len++;
	return (len);
}

int		get_env_value_index(char *key)
{
	int		index;
	char	*tmp;

	index = 0;
	while (g_env && g_env[index])
	{
		if ((tmp = ft_strstr(g_env[index], key)) && tmp[ft_strlen(key)] == '=')
			return (index);
		index++;
	}
	return (-1);
}

char	*get_env_value(char *key)
{
	char	*value;
	int		index;

	index = get_env_value_index(key);
	if (index == -1)
		return (NULL);
	value = g_env[index] + ft_strlen(key) + 1;
	return (value);
}

int		del_env_value(char *name)
{
	int		env_len;
	int		index;
	char	*value_to_del;

	env_len = get_env_len();
	index = get_env_value_index(name);
	if (index != -1)
	{
		value_to_del = g_env[index];
		while (index < env_len)
		{
			g_env[index] = g_env[index + 1];
			index++;
		}
		free(value_to_del);
		return (1);
	}
	return (0);
}

int		add_env_value(char *key, char *value)
{
	int		env_len;
	int		index;
	char	*tmp;

	env_len = get_env_len();
	if ((index = get_env_value_index(key)) != -1)
	{
		tmp = g_env[index];
		g_env[index] = ft_strjoin3(key, "=", value);
		free(tmp);
	}
	else if (env_len < ENV_SIZE)
		g_env[env_len] = ft_strjoin3(key, "=", value);
	else
		return (0);
	return (1);
}
