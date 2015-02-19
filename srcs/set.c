/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/03 17:28:43 by ycribier          #+#    #+#             */
/*   Updated: 2014/01/04 12:27:54 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "pipex.h"

void	chk_access(char *path)
{
	if (access(path, F_OK) == -1)
		error_msg_exit(path, "no such file or directory.");
	if (access(path, R_OK) == -1)
		error_msg_exit(path, "permission denied.");
}

int		chk_open(char *path, int oflags, mode_t mode)
{
	int	fd;

	fd = open(path, oflags, mode);
	if (fd == -1)
		error_msg_exit(path, "open failed.");
	return (fd);
}
