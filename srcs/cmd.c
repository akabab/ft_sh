/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/31 15:31:29 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/18 14:40:44 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"

char	*get_cmd_path(char *cmd)
{
	char	*path_value;
	char	**cmds_path_tab;
	char	*cmd_path;

	path_value = get_env_value("PATH");
	if (path_value)
	{
		cmds_path_tab = ft_strsplit(path_value, ':');
		while (cmds_path_tab && *cmds_path_tab)
		{
			cmd_path = ft_strjoin3(*cmds_path_tab, "/", cmd);
			if (access(cmd_path, F_OK) == 0)
			{
				if (access(cmd_path, X_OK) == 0)
					return (cmd_path);
				ft_printf("%s: permission denied.\n", cmd);
			}
			cmds_path_tab++;
		}
	}
	return (NULL);
}
