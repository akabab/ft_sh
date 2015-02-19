/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 21:56:21 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/19 11:01:58 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

# define ENV_SIZE 2048

extern char	**environ;

char	**g_env;

typedef struct	s_cmd
{
	char		*name;
	char		*path;
	int			ac;
	char		**av;
}				t_cmd;

/*
**		env_tools.c
*/
int		get_env_len(char **env);
int		get_env_value_index(char *name);
char	*get_env_value(char *name);
int		del_env_value(char *name);
int		add_env_value(char *name, char *value);

/*
**		env.c
*/
void	unset_env(t_cmd *cmd);
void	set_env(t_cmd *cmd);
void	print_env(void);
void	cpy_env(void);

/*
**		cd.c
*/
void	change_dir(t_cmd *cmd);

/*
**		cmd.c
*/
char	*get_cmd_path(char *cmd);

#endif
