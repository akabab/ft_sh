/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 21:58:07 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/19 11:15:17 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"

void	print_prompt(void)
{
	char	*pwd;

	if ((pwd = get_env_value("PWD")))
		ft_putstr(pwd);
	ft_putstr("$> ");
}

void	split_cmd(char *entry, t_cmd *cmd)
{
	char	**tmp;
	int		ac;

	tmp = ft_strsplit(entry, ' ');
	if (!tmp)
		ft_printf("split failed.\n");
	ac = 0;
	while (tmp[ac])
		ac++;
	cmd->name = tmp[0];
	cmd->path = tmp[0];
	cmd->ac = ac;
	cmd->av = tmp;
}

void	execute_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		sig;

	pid = fork();
	if (pid < 0)
		ft_printf("fork failed.\n");
	if (pid == 0)
	{
		execve(cmd->path, cmd->av, g_env);
		ft_printf("%s: no such file or directory.\n", cmd->path);
		_exit(1);
	}
	else
		wait(&sig);
}

void	execute(char *entry)
{
	t_cmd	cmd;

	split_cmd(entry, &cmd);
	if (!cmd.name)
		return ;
	else if (ft_strequ(cmd.name, "exit"))
		_exit(1);
	else if (ft_strequ(cmd.name, "cd"))
		change_dir(&cmd);
	else if (ft_strequ(cmd.name, "env"))
		print_env();
	else if (ft_strequ(cmd.name, "setenv"))
		set_env(&cmd);
	else if (ft_strequ(cmd.name, "unsetenv"))
		unset_env(&cmd);
	else
	{
		if (cmd.name[0] != '/')
			cmd.path = get_cmd_path(cmd.name);
		if (!cmd.path)
			cmd.path = cmd.name;
		execute_cmd(&cmd);
	}
}

int		main(void)
{
	char	*entry;

	cpy_env();
	while (1)
	{
		entry = NULL;
		print_prompt();
		if (get_next_line(0, &entry) == 0)
			_exit(1);
		execute(entry);
		free(entry);
	}
	return (0);
}
