/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 20:10:37 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/19 17:55:38 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static void		cd_update_env(void)
{
	char	*pwd;
	char	*cwd;

	pwd = get_env_value("PWD");
	if (pwd)
		add_env_value("OLDPWD", pwd);
	cwd = getcwd(NULL, 0);
	add_env_value("PWD", cwd);
	free(cwd);
}

static void		cd_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD");
	if (oldpwd)
		chdir(oldpwd);
}

static void		cd_home(void)
{
	char	*home;

	home = get_env_value("HOME");
	if (home)
		chdir(home);
}

static int		cd_check_access(char *path)
{
	struct stat		stats;

	if (access(path, F_OK) == -1)
		ft_printf("%s: no such file or directory.\n", path);
	else
	{
		if (lstat(path, &stats) == 0)
		{
			if (S_ISDIR(stats.st_mode))
			{
				if (access(path, X_OK) == -1)
					ft_printf("%s: permission denied.\n", path);
				else
					return (1);
			}
			else
				ft_printf("%s: not a directory.\n", path);
		}
	}
	return (0);
}

void			change_dir(t_cmd *cmd)
{
	char	*path;

	if (cmd->ac < 3)
	{
		path = cmd->av[1];
		if (cmd->ac == 1 || ft_strequ(path, "~"))
			cd_home();
		else if (ft_strequ(path, "-"))
			cd_oldpwd();
		else if (cd_check_access(path))
			chdir(path);
	}
	else
		ft_putendl("usage: cd [path] | [~] (HOME) | [-] (OLDPWD)");
	cd_update_env();
}
