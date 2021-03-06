/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 21:58:07 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/20 15:56:33 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"

void	clean_entry(char *entry)
{
	while (entry && *entry)
	{
		if (*entry == '\t')
			*entry = ' ';
		entry++;
	}
}

void	split_cmd(char *entry, t_cmd *cmd)
{
	char	**tmp;
	int		ac;

	clean_entry(entry);
	tmp = ft_strsplit(entry, ' ');
	if (!tmp)
		ft_putendl("split failed.");
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
		ft_putendl("fork failed.");
	if (pid == 0)
	{
		signal_reset();
		execve(cmd->path, cmd->av, g_env);
		ft_printf("%s: command not found.\n", cmd->path);
		exit(1);
	}
	else
	{
		signal(SIGINT, sigint_one);
		wait(&sig);
	}
}

void	execute(char *entry)
{
	t_cmd	cmd;

	split_cmd(entry, &cmd);
	if (!cmd.name)
		return ;
	else if (ft_strequ(cmd.name, "exit"))
		exit(1);
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
	free_cmd(&cmd);
}

int		main(int ac, char *av[], char *env[])
{
	char	*entry;

	(void)ac;
	(void)av;
	cpy_env(env);
	while (1)
	{
		entry = NULL;
		print_prompt();
		signal(SIGINT, sigint_two);
		if (get_next_line(0, &entry) != 1)
			exit(0);
		execute(entry);
		free(entry);
	}
	return (0);
}
