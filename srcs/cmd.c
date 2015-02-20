/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/31 15:31:29 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/20 18:27:10 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"

static char		*get_path_from_env(char *cmd, char **cmds_path_tab)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (cmds_path_tab && cmds_path_tab[i])
	{
		cmd_path = ft_strjoin3(cmds_path_tab[i], "/", cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			else
				ft_printf("%s: permission denied.\n", cmd);
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char			*get_cmd_path(char *cmd)
{
	char	*path_value;
	char	**cmds_path_tab;
	char	*cmd_path;

	cmd_path = NULL;
	if ((path_value = get_env_value("PATH")))
	{
		cmds_path_tab = ft_strsplit(path_value, ':');
		cmd_path = get_path_from_env(cmd, cmds_path_tab);
		free_tab(&cmds_path_tab);
	}
	return (cmd_path);
}

#include <stdio.h>

void			clean_path(char **path)
{
	char	**tab;
	char	*home;
	char	*clean_path;

	if (!(home = get_env_value("HOME")))
		return ;
	if (ft_strchr(*path, '~'))
	{
		tab = ft_strsplit_once(*path, '~');
		// printf("%s-%p\n", tab[0], tab[0]);
		// printf("%s-%p\n", tab[1], tab[1]);
		if ((clean_path = ft_strjoin3(tab[0], home, tab[1])))
		{
			free_tab(&tab);
			// free(*path);
			*path = clean_path;
		}
	}
}

void			free_cmd(t_cmd *cmd)
{
	free_tab(&cmd->av);
	if (cmd->path != cmd->name)
		free(cmd->path);
}
