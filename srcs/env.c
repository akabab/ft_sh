/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 17:57:58 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/19 18:24:07 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env(t_cmd *cmd)
{
	int		i;

	i = 1;
	while (i < cmd->ac)
	{
		del_env_value(cmd->av[i]);
		i++;
	}
}

void	set_env(t_cmd *cmd)
{
	if (cmd->ac != 3)
		ft_putendl("usage: setenv [name] [value]");
	else
		add_env_value(cmd->av[1], cmd->av[2]);
}

void	print_env(void)
{
	int		i;

	i = 0;
	while (g_env && g_env[i])
	{
		ft_putendl(g_env[i]);
		i++;
	}
}

void	cpy_env(char *env[])
{
	int		i;

	g_env = ft_memalloc(sizeof(char *) * (ENV_SIZE + 1));
	if (!g_env)
	{
		ft_putendl("malloc failed.");
		return ;
	}
	i = 0;
	while (env && env[i])
	{
		g_env[i] = ft_strdup(env[i]);
		i++;
	}
	g_env[i] = NULL;
}
