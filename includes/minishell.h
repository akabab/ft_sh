/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 21:56:21 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/19 18:02:07 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>

# define ENV_SIZE 2048

char		**g_env;

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
void			print_prompt(void);

/*
**		env_tools.c
*/
int				get_env_len(void);
int				get_env_value_index(char *key);
char			*get_env_value(char *key);
int				del_env_value(char *key);
int				add_env_value(char *key, char *value);

/*
**		env.c
*/
void			unset_env(t_cmd *cmd);
void			set_env(t_cmd *cmd);
void			print_env(void);
void			cpy_env(char *env[]);

/*
**		cd.c
*/
void			change_dir(t_cmd *cmd);

/*
**		cmd.c
*/
char			*get_cmd_path(char *cmd);
void			free_cmd(t_cmd *cmd);

/*
**		COLOR
*/
# define RED		"31"
# define GREEN		"32"
# define YELLOW		"33"
# define BLUE		"34"
# define PINK		"35"
# define GRBL		"36"
# define GREY		"37"
# define NO			"0"
# define C(X)		"\033["X"m"
# define CC(X)		"\033[3"X"m"
# define CB(X)		"\x1B[48;1;"X"m"
# define CBNO		"\x1B[0m"

#endif
